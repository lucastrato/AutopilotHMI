#include <gtest/gtest.h>

#include "HeadingController.h"

TEST(HeadingController, PositiveErrorProducesPositiveRudder)
{
    HeadingController controller;

    const double rudder = controller.computeRudderSetPoint(40.0, 0.0);

    EXPECT_GT(rudder, 0.0);
}

TEST(HeadingController, WrapAroundClockwise)
{
    HeadingController controller;

    const double rudder = controller.computeRudderSetPoint(10.0, 350.0);

    EXPECT_GT(rudder, 0.0);
}

TEST(HeadingController, WrapAroundCounterClockwise)
{
    HeadingController controller;

    const double rudder = controller.computeRudderSetPoint(350.0, 10.0);

    EXPECT_LT(rudder, 0.0);
}

TEST(HeadingController, RudderIsClamped)
{
    HeadingController controller;

    const double rudder = controller.computeRudderSetPoint(180.0, 0.0);

    EXPECT_LE(rudder, 35.0);
}