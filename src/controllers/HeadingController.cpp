#include "HeadingController.h"
#include "Constants.h"
#include "MathUtils.h"

#include <algorithm>

auto HeadingController::computeRudderSetPoint(double targetHeading, double currentHeading) const
    -> double
{
    double error = MathUtils::normalizeHeading(targetHeading - currentHeading);

    const double rudder = error * Constants::HeadingControllerKp;

    return std::clamp(rudder, -Constants::RudderMaxAngle, Constants::RudderMaxAngle);
}