#pragma once

#include <vector>

#include "ControllerState.h"
#include "HeadingController.h"
#include "IAutopilotCommands.h"
#include "IControllerDriver.h"
#include "IControllerObserver.h"

class AutopilotController : public IAutopilotCommands
{
public:
    explicit AutopilotController(IControllerDriver& driver);

    [[nodiscard]] auto state() const -> const ControllerState&;

    void update();

    void addObserver(IControllerObserver* observer);
    void removeObserver(IControllerObserver* observer);

    void setTargetHeading(double heading) override;
    void setRudder(double rudderAngle) override;
    void setMode(AutopilotMode mode) override;

private:
    void notifyObservers();

    ControllerState m_state;
    IControllerDriver& m_driver;

    HeadingController m_headingController;

    std::vector<IControllerObserver*> m_observers;
};
