#pragma once

namespace MathUtils
{

[[nodiscard]]
auto normalizeHeading(double heading) -> double;

[[nodiscard]]
auto headingError(double target, double current) -> double;
} // namespace MathUtils