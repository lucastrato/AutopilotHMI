#include "AutopilotController.h"

AutopilotController::AutopilotController(IControllerDriver& driver) : m_driver(driver) {}

void AutopilotController::update()
{
    const DriverState& driverState = m_driver.readState();

    m_state.heading = driverState.heading;
    m_state.rudderAngle = driverState.rudderAngle;

    notifyObservers();
}

auto AutopilotController::state() const -> const ControllerState&
{
    return m_state;
}

void AutopilotController::addObserver(IControllerObserver* observer)
{
    m_observers.push_back(observer);
}

void AutopilotController::removeObserver(IControllerObserver* observer)
{
    auto iter = std::remove(m_observers.begin(), m_observers.end(), observer);
    m_observers.erase(iter, m_observers.end());
}

void AutopilotController::notifyObservers()
{
    for (auto* observer : m_observers)
    {
        observer->onStateChanged(m_state);
    }
}

void AutopilotController::increaseTargetHeading()
{
    m_state.targetHeading += 1.0;

    notifyObservers();
}

void AutopilotController::decreaseTargetHeading()
{
    m_state.targetHeading -= 1.0;

    notifyObservers();
}
