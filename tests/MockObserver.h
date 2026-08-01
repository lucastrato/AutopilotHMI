#pragma once

#include "IControllerObserver.h"

class MockObserver : public IControllerObserver
{
public:
    bool notified = false;
    ControllerState lastState{};

    void onStateChanged(const ControllerState& state) override
    {
        notified = true;
        lastState = state;
    }
};