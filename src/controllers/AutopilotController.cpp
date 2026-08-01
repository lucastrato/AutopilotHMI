#include <algorithm>
#include <iostream>

#include "AutopilotController.h"
#include "Constants.h"
#include "MathUtils.h"

AutopilotController::AutopilotController(IControllerDriver& driver) : m_driver(driver) {}

void AutopilotController::update()
{
    const DriverState& driverState = m_driver.readState();
    DriverCommands commands;

    m_state.heading = MathUtils::normalizeHeading(driverState.heading);
    m_state.rudderAngle =
        std::clamp(driverState.rudderAngle, -Constants::RudderMaxAngle, Constants::RudderMaxAngle);

    switch (m_state.mode)
    {
        case AutopilotMode::Standby:
            break;

        case AutopilotMode::Manual:
            commands.rudderSetPoint = m_state.targetRudderAngle;

            m_driver.writeCommands(commands);
            break;

        case AutopilotMode::Auto:
            commands.rudderSetPoint =
                m_headingController.computeRudderSetPoint(m_state.targetHeading, m_state.heading);

            m_driver.writeCommands(commands);
            break;
    }

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

void AutopilotController::setTargetHeading(double heading)
{
    m_state.targetHeading = MathUtils::normalizeHeading(heading);

    notifyObservers();
}

void AutopilotController::setRudder(double rudderAngle)
{
    m_state.targetRudderAngle =
        std::clamp(rudderAngle, -Constants::RudderMaxAngle, Constants::RudderMaxAngle);

    notifyObservers();
}

void AutopilotController::setMode(AutopilotMode mode)
{
    if (m_state.mode == mode)
    {
        return;
    }

    m_state.mode = mode;
    DriverCommands commands;

    switch (mode)
    {
        case AutopilotMode::Standby:
            // Reset operator references
            m_state.targetHeading = m_state.heading;
            // Release rudder
            commands.rudderSetPoint = 0.0;
            m_driver.writeCommands(commands);
            break;

        case AutopilotMode::Manual:
            // Operator starts from current rudder position
            commands.rudderSetPoint = m_state.rudderAngle;
            m_driver.writeCommands(commands);
            // Keep target heading aligned with current heading
            m_state.targetHeading = m_state.heading;
            break;

        case AutopilotMode::Auto:
            // Hold the current course
            m_state.targetHeading = m_state.heading;
            break;
    }
    notifyObservers();
}
