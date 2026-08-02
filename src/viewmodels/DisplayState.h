/**
 * @file DisplayState.h
 * @brief Represents the state data displayed by the user interface.
 *
 * DisplayState contains the subset of autopilot information required by the
 * HMI layer to present the current system status to the operator.
 *
 * This structure acts as a data transfer object between the controller logic
 * and the display layer, keeping the UI independent from the internal
 * controller implementation.
 */

#pragma once

#include "AutopilotMode.h"

struct DisplayState
{
    /**
     * @brief Current vessel heading in degrees.
     */
    double heading = 0.0;

    /**
     * @brief Requested target heading in degrees.
     */
    double targetHeading = 0.0;

    /**
     * @brief Current rudder angle in degrees.
     */
    double rudderAngle = 0.0;

    /**
     * @brief Current autopilot operating mode.
     *
     * Defaults to Standby when no active control mode has been selected.
     */
    AutopilotMode mode = AutopilotMode::Standby;
};