#pragma once

#include "AutopilotMode.h"

struct DisplayState
{
    double heading = 0.0;
    double targetHeading = 0.0;
    double rudderAngle = 0.0;

    AutopilotMode mode = AutopilotMode::Standby;
};