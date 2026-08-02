/**
 * @file HeadingController.h
 * @brief Heading control algorithm.
 *
 * Implements the control law used in automatic steering mode.
 *
 * The controller computes a rudder command based on the difference
 * between the current vessel heading and the desired target heading.
 *
 * The heading error is normalized in the range [-180°, 180°] to ensure
 * the vessel always takes the shortest rotation direction.
 */

#pragma once

/**
 * @class HeadingController
 * @brief Converts heading error into rudder commands.
 *
 * The HeadingController implements a proportional controller:
 *
 *     rudderCommand = Kp * headingError
 *
 * The generated rudder command is limited to the configured maximum
 * rudder angle.
 *
 * Responsibilities:
 *
 *  - Calculate shortest-path heading error.
 *  - Apply controller gain.
 *  - Limit rudder output.
 */

class HeadingController
{
public:
    HeadingController() = default;

    /**
     * @brief Computes the rudder command.
     *
     * @param currentHeading Current vessel heading in degrees.
     * @param targetHeading Desired heading in degrees.
     *
     * @return Signed rudder command in degrees.
     *
     * Positive values command a turn to starboard.
     * Negative values command a turn to port.
     */

    [[nodiscard]] auto computeRudderSetPoint(double targetHeading, double currentHeading) const
        -> double;

private:
};
