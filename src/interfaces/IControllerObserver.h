#pragma once

#include "ControllerState.h"

class IControllerObserver
{
public:
    virtual ~IControllerObserver() = default;

    virtual void onStateChanged(const ControllerState& state) = 0;
};
