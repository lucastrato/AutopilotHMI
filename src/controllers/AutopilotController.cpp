/**
 * @file AutopilotController.cpp
 * @brief Implementation of the autopilot control logic.
 */

#include <algorithm>
// #include <iostream>

#include "AutopilotController.h"
#include "Constants.h"
#include "MathUtils.h"

AutopilotController::AutopilotController(IControllerDriver& driver) : m_driver(driver) {}

void AutopilotController::update()
{
    /*
     * Update cycle:
     *
     * 1. Read latest vehicle data.
     * 2. Update internal state.
     * 3. Generate commands according to current mode.
     * 4. Send commands to driver.
     * 5. Notify observers.
     */

    const DriverState& driverState = m_driver.readState();
    DriverCommands commands;

    m_state.heading = MathUtils::normalizeHeading(driverState.heading);
    m_state.rudderAngle =
        std::clamp(driverState.rudderAngle, -Constants::RudderMaxAngle, Constants::RudderMaxAngle);

    switch (m_state.mode)
    {
        case AutopilotMode::Standby:
            // No control action required.
            break;

        case AutopilotMode::Manual:
            // In manual mode the operator directly controls the rudder.
            commands.rudderSetPoint = m_state.targetRudderAngle;

            m_driver.writeCommands(commands);
            break;

        case AutopilotMode::Auto:
            // Automatic steering computes rudder correction from heading error.
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
            /*
             * When entering standby:
             * - stop active steering commands.
             * - synchronize target heading with current heading.
             */

            m_state.targetHeading = m_state.heading;
            commands.rudderSetPoint = 0.0;
            m_driver.writeCommands(commands);
            break;

        case AutopilotMode::Manual:

            /*
             * Manual control starts from the current rudder position
             * to avoid a sudden command jump.
             */

            commands.rudderSetPoint = m_state.rudderAngle;
            m_driver.writeCommands(commands);
            m_state.targetHeading = m_state.heading;
            break;

        case AutopilotMode::Auto:

            /*
             * Auto mode initially holds the current course.
             * The operator can then select a different target heading.
             */

            m_state.targetHeading = m_state.heading;
            break;
    }
    notifyObservers();
}
