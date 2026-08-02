#include "MathUtils.h"

#include "Constants.h"

namespace MathUtils
{

auto normalizeHeading(double heading) -> double
{
    while (heading >= Constants::FullCircleDeg)
    {
        heading -= Constants::FullCircleDeg;
    }

    while (heading < 0.0)
    {
        heading += Constants::FullCircleDeg;
    }

    return heading;
}

double headingError(double target, double current)
{
    double error = normalizeHeading(target - current);

    if (error > Constants::HalfCircleDeg)
        error -= Constants::FullCircleDeg;

    return error;
}

} // namespace MathUtils