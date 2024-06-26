/*
 * Copyright (C) 2018
 *
 * This file is part of paparazzi.
 *
 * paparazzi is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * paparazzi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with paparazzi; see the file COPYING.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#ifndef OPTICAL_FLOW_HOVER_H_
#define OPTICAL_FLOW_HOVER_H_

#include "std.h"

extern bool oscphi;
extern bool osctheta;
extern bool derotated;
extern bool cov_method;         ///< method to calculate the covariance: between thrust and div / angle and flow (0) or div and div past / flow and past flow(1)
extern uint8_t hover_method;    ///< Method used to hover 0 = All axis after each other; 1 = all axis at the same time; 2 = vertical only, use relation to set horizontal

extern struct OpticalFlowHoverControl of_hover_ctrl_X;
extern struct OpticalFlowHoverControl of_hover_ctrl_Y;
extern struct OpticalFlowHoverControl of_hover_ctrl_Z;

// The module functions
extern void optical_flow_hover_init(void);

extern void guidance_module_enter(void);
extern void guidance_module_run(bool in_flight);

#endif /* OPTICAL_FLOW_LANDING_H_ */

