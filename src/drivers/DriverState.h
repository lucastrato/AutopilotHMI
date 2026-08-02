/**
 * @file DriverState.h
 * @brief Represents the current state reported by the controller driver.
 *
 * DriverState contains the feedback data retrieved from the underlying
 * hardware or communication interface.
 *
 * This structure is used as a data transfer object between the driver layer
 * and the controller logic, keeping the control algorithms independent from
 * the specific hardware implementation.
 */

#pragma once

struct DriverState
{
    /**
     * @brief Current vessel heading in degrees.
     */
    double heading{0.0};

    /**
     * @brief Current rudder angle in degrees.
     */
    double rudderAngle{0.0};

    /**
     * @brief Current vessel speed.
     *
     * The unit depends on the driver implementation (e.g. knots or meters
     * per second) and should be documented by the concrete driver.
     */
    double speed{0.0};
};