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
