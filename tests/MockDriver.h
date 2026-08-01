#pragma once

#include "IControllerDriver.h"

class MockDriver : public IControllerDriver
{
public:
    DriverState driverState{};
    DriverCommands lastCommands{};

    int writeCommandCalls = 0;

    [[nodiscard]] auto readState() -> DriverState override
    {
        return driverState;
    }

    void writeCommands(const DriverCommands& commands) override
    {
        lastCommands = commands;
    }
};
