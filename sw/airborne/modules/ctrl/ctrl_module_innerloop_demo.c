/*
 * Copyright (C) 2015
 *
 * This file is part of Paparazzi.
 *
 * Paparazzi is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * Paparazzi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Paparazzi; see the file COPYING.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

/**
 * @file modules/ctrl/ctrl_module_innerloop_demo.h
 * @brief example empty controller
 *
 */

#include "modules/ctrl/ctrl_module_innerloop_demo.h"
#include "state.h"
#include "modules/radio_control/radio_control.h"
#include "generated/radio.h"
#include "firmwares/rotorcraft/stabilization.h"

struct ctrl_module_demo_struct {
  int rc_x;
  int rc_y;
  int rc_z;
  int rc_t;

} ctrl_module_demo;

float ctrl_module_demo_pr_ff_gain = 0.2f;  // Pitch/Roll
float ctrl_module_demo_pr_d_gain = 0.1f;
float ctrl_module_demo_y_ff_gain = 0.4f;   // Yaw
float ctrl_module_demo_y_d_gain = 0.05f;

void ctrl_module_init(void)
{
  ctrl_module_demo.rc_x = 0;
  ctrl_module_demo.rc_y = 0;
  ctrl_module_demo.rc_z = 0;
  ctrl_module_demo.rc_t = 0;
}

// simple rate control without reference model nor attitude
static void ctrl_module_run(bool in_flight)
{
  if (!in_flight) {
    // Reset integrators
    stabilization.cmd[COMMAND_ROLL] = 0;
    stabilization.cmd[COMMAND_PITCH] = 0;
    stabilization.cmd[COMMAND_YAW] = 0;
    stabilization.cmd[COMMAND_THRUST] = 0;
  } else {
    stabilization.cmd[COMMAND_ROLL]   = ctrl_module_demo.rc_x * ctrl_module_demo_pr_ff_gain -
      stateGetBodyRates_i()->p * ctrl_module_demo_pr_d_gain;
    stabilization.cmd[COMMAND_PITCH]  = ctrl_module_demo.rc_y * ctrl_module_demo_pr_ff_gain -
      stateGetBodyRates_i()->q * ctrl_module_demo_pr_d_gain;
    stabilization.cmd[COMMAND_YAW]    = ctrl_module_demo.rc_z * ctrl_module_demo_y_ff_gain -
      stateGetBodyRates_i()->r * ctrl_module_demo_y_d_gain;
    stabilization.cmd[COMMAND_THRUST] = ctrl_module_demo.rc_t;
  }
}


////////////////////////////////////////////////////////////////////
// Call our controller
void guidance_module_enter(void)
{
  ctrl_module_init();
}

void guidance_module_run(bool in_flight)
{
  // -MAX_PPRZ to MAX_PPRZ
  ctrl_module_demo.rc_t = radio_control.values[RADIO_THROTTLE];
  ctrl_module_demo.rc_x = radio_control.values[RADIO_ROLL];
  ctrl_module_demo.rc_y = radio_control.values[RADIO_PITCH];
  ctrl_module_demo.rc_z = radio_control.values[RADIO_YAW];
  // Call full inner-/outerloop / horizontal-/vertical controller:
  ctrl_module_run(in_flight);
}

