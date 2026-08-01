#pragma once

#include <memory>
#include <vector>

#include "ControllerState.h"
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

    void increaseTargetHeading() override;
    void decreaseTargetHeading() override;

private:
    void notifyObservers();

    ControllerState m_state;
    IControllerDriver& m_driver;

    std::vector<IControllerObserver*> m_observers;
};
