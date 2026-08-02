/**
 * @file IAutopilotCommands.h
 * @brief Interface for sending operator commands to the autopilot system.
 *
 * This interface defines the commands that can be requested by external
 * components, such as the QML ViewModel.
 *
 * The interface separates the user interface from the autopilot controller
 * implementation, allowing different command sources or test environments
 * to interact with the controller without depending on its concrete class.
 *
 * The UI does not know that the implementation is AutopilotController.
 *
 * That means:
 *
 * you can unit-test SteeringViewModel with a mock IAutopilotCommands
 * you can replace the controller implementation later
 * the QML layer stays independent from the control logic
 */

#pragma once

#include "AutopilotMode.h"

/**
 * @class IAutopilotCommands
 * @brief Abstract command interface for autopilot control.
 *
 * Implementations of this interface are responsible for receiving
 * high-level operator commands and applying them to the autopilot system.
 *
 * Typical usage:
 *
 *     QML
 *       |
 *       v
 * SteeringViewModel
 *       |
 *       v
 * IAutopilotCommands
 *       |
 *       v
 * AutopilotController
 *
 * The interface does not define how commands are executed, only the
 * available operations.
 */
class IAutopilotCommands
{
public:
    /**
     * @brief Virtual destructor.
     *
     * Required to allow safe destruction of derived implementations
     * through an interface pointer.
     */
    virtual ~IAutopilotCommands() = default;

    /**
     * @brief Sets the desired heading.
     *
     * The target heading is used by automatic steering algorithms as
     * the navigation reference.
     *
     * @param heading Desired heading in degrees.
     */
    virtual void setTargetHeading(double heading) = 0;

    /**
     * @brief Sets the manual rudder command.
     *
     * This command is typically applied only when the autopilot is
     * operating in manual mode.
     *
     * @param rudderAngle Requested rudder angle in degrees.
     */
    virtual void setRudder(double rudderAngle) = 0;

    /**
     * @brief Changes the current autopilot operating mode.
     *
     * @param mode New autopilot mode.
     */
    virtual void setMode(AutopilotMode mode) = 0;
};
