#pragma once

class HeadingController
{
public:
    HeadingController() = default;

    [[nodiscard]] auto computeRudderSetPoint(double targetHeading, double currentHeading) const
        -> double;

private:
};
