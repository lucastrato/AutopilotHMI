/**
 * @file AutopilotController.h
 * @brief Main autopilot control logic.
 *
 * The AutopilotController coordinates the interaction between:
 *  - the vehicle/controller driver
 *  - the heading controller
 *  - the application state
 *  - external observers (for example the UI layer)
 *
 * It implements the IAutopilotCommands interface to receive
 * operator commands from the application layer.
 */

#pragma once

#include <vector>

#include "ControllerState.h"
#include "HeadingController.h"
#include "IAutopilotCommands.h"
#include "IControllerDriver.h"
#include "IControllerObserver.h"

/**
 * @class AutopilotController
 * @brief Handles autopilot state management and command generation.
 *
 * Responsibilities:
 *  - Maintain the current autopilot state.
 *  - Process operator commands.
 *  - Execute the selected control mode.
 *  - Generate commands for the controller driver.
 *  - Notify registered observers about state changes.
 *
 * Supported modes:
 *
 *  - Standby:
 *      No automatic control is applied.
 *
 *  - Manual:
 *      The commanded rudder angle is directly sent to the driver.
 *
 *  - Auto:
 *      The heading controller computes the required rudder command
 *      to reach and maintain the selected heading.
 *
 * The controller does not:
 *  - communicate directly with the UI.
 *  - handle hardware communication details.
 *  - perform signal rendering.
 */
class AutopilotController : public IAutopilotCommands
{
public:
    /**
     * @brief Creates an autopilot controller.
     *
     * @param driver Driver interface used to read vehicle state and
     *               send control commands.
     */
    explicit AutopilotController(IControllerDriver& driver);

    /**
     * @brief Returns the current controller state.
     *
     * @return Current autopilot state.
     */
    [[nodiscard]]
    auto state() const -> const ControllerState&;

    /**
     * @brief Executes one controller update cycle.
     *
     * Reads the latest vehicle state, applies the current control mode,
     * sends commands to the driver and notifies observers.
     *
     * This function is expected to be called periodically.
     */
    void update();

    /**
     * @brief Registers an observer.
     *
     * Observers are notified whenever the controller state changes.
     */
    void addObserver(IControllerObserver* observer);

    /**
     * @brief Removes an observer.
     */
    void removeObserver(IControllerObserver* observer);

    /**
     * @brief Sets the desired heading.
     *
     * @param heading Target heading in degrees.
     */
    void setTargetHeading(double heading) override;

    /**
     * @brief Sets the desired rudder angle.
     *
     * @param rudderAngle Rudder command in degrees.
     */
    void setRudder(double rudderAngle) override;

    /**
     * @brief Changes the autopilot operating mode.
     *
     * @param mode New autopilot mode.
     */
    void setMode(AutopilotMode mode) override;

private:
    /**
     * @brief Notifies all registered observers of a state update.
     */
    void notifyObservers();

    /// Current autopilot state.
    ControllerState m_state;

    /// Interface used for communication with the vehicle controller.
    IControllerDriver& m_driver;

    /// Heading controller used in automatic steering mode.
    HeadingController m_headingController;

    /// List of components interested in state changes.
    std::vector<IControllerObserver*> m_observers;
};