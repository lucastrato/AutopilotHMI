#pragma once

#include "AutopilotMode.h"

class IAutopilotCommands
{
public:
    virtual ~IAutopilotCommands() = default;

    virtual void setTargetHeading(double heading) = 0;
    virtual void setRudder(double rudderAngle) = 0;
    virtual void setMode(AutopilotMode mode) = 0;
};