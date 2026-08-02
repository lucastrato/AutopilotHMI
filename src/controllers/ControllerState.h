/**
 * @file ControllerState.h
 * @brief Defines the state representation used by the autopilot controller.
 *
 * This file contains the data structures used to represent the current
 * operating state of the autopilot system, including the active mode and
 * related controller information.
 *
 * This structure acts as a container shared between the controller logic and
 * the UI layer, providing the current mode and navigation-related values.
 */

#pragma once

#include "AutopilotMode.h"

struct ControllerState
{
    double heading{0.0};
    double targetHeading{0.0};
    double rudderAngle{0.0};
    double targetRudderAngle{0.0};
    double speed{0.0};

    double latitude{0.0};
    double longitude{0.0};

    AutopilotMode mode = AutopilotMode::Standby;
    bool autopilotEnabled{false};
};