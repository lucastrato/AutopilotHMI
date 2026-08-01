#pragma once

#include "DriverState.h"

class IControllerDriver
{
public:
    virtual ~IControllerDriver() = default;

    virtual auto readState() -> DriverState = 0;
};