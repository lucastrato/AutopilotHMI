#pragma once

#include "DriverCommands.h"
#include "DriverState.h"

/**
 * @class IControllerDriver
 * @brief Interface for communication with the low-level controller driver.
 *
 * The IControllerDriver interface defines the abstraction layer between the
 * autopilot control logic and the hardware-specific driver implementation.
 *
 * Implementations of this interface are responsible for retrieving the current
 * driver state (e.g. sensor feedback, actuator status) and sending control
 * commands to the underlying hardware or communication interface.
 *
 * This separation allows the controller logic to remain independent from the
 * specific communication protocol or hardware platform.
 */
class IControllerDriver
{
public:
    /**
     * @brief Virtual destructor.
     *
     * Ensures that derived driver implementations are properly destroyed when
     * accessed through an IControllerDriver pointer.
     */
    virtual ~IControllerDriver() = default;

    /**
     * @brief Reads the current state from the controller driver.
     *
     * Retrieves the latest available driver feedback, such as measured heading,
     * rudder position, actuator status, or other hardware-related information.
     *
     * @return Current driver state snapshot.
     */
    virtual auto readState() -> DriverState = 0;

    /**
     * @brief Sends commands to the controller driver.
     *
     * Writes the requested commands to the underlying hardware interface.
     * The implementation is responsible for translating these commands into
     * the appropriate communication protocol or hardware operation.
     *
     * @param commands Command set to be applied by the driver.
     */
    virtual void writeCommands(const DriverCommands& commands) = 0;
};