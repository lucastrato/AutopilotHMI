/**
 * @file HeadingController.cpp
 * @brief Implementation of the heading controller.
 */

#include "HeadingController.h"
#include "Constants.h"
#include "MathUtils.h"

#include <algorithm>

auto HeadingController::computeRudderSetPoint(double targetHeading, double currentHeading) const
    -> double
{
    /// Computes the shortest rotation direction.
    double error = MathUtils::headingError(targetHeading, currentHeading);
    /// Apply proportional control.
    const double rudder = error * Constants::HeadingControllerKp;
    /// Prevent commands outside the physical rudder limits.
    return std::clamp(rudder, -Constants::RudderMaxAngle, Constants::RudderMaxAngle);
}