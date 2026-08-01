#pragma once

#include "DriverCommands.h"
#include "DriverState.h"

class IControllerDriver
{
public:
    virtual ~IControllerDriver() = default;

    virtual auto readState() -> DriverState = 0;

    virtual void writeCommands(const DriverCommands& commands) = 0;
};