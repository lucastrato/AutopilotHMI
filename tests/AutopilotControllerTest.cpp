#include <gtest/gtest.h>

#include "AutopilotController.h"
#include "MockDriver.h"
#include "MockObserver.h"

TEST(AutopilotController, UpdateCopiesHeadingFromDriver)
{
    MockDriver driver;

    driver.driverState.heading = 123.4;

    AutopilotController controller(driver);

    controller.update();

    EXPECT_DOUBLE_EQ(controller.state().heading, 123.4);
}

TEST(AutopilotController, ObserverIsNotifiedAfterUpdate)
{
    MockDriver driver;
    MockObserver observer;

    AutopilotController controller(driver);

    controller.addObserver(&observer);

    controller.update();

    EXPECT_TRUE(observer.notified);
}

TEST(AutopilotController, UpdateCopiesDriverState)
{
    MockDriver driver;

    driver.driverState.heading = 123.4;
    driver.driverState.rudderAngle = -8.2;

    AutopilotController controller(driver);

    controller.update();

    EXPECT_DOUBLE_EQ(controller.state().heading, 123.4);
    EXPECT_DOUBLE_EQ(controller.state().rudderAngle, -8.2);
}

TEST(AutopilotController, PositiveHeadingErrorProducesPositiveRudderCommand)
{
    MockDriver driver;

    driver.driverState.heading = 0.0;

    AutopilotController controller(driver);

    controller.setMode(AutopilotMode::Auto);

    controller.setTargetHeading(40.0);

    controller.update();

    EXPECT_GT(driver.lastCommands.rudderSetPoint, 0.0);
}

TEST(AutopilotController, NegativeHeadingErrorProducesNegativeRudderCommand)
{
    MockDriver driver;

    driver.driverState.heading = 40.0;

    AutopilotController controller(driver);

    controller.setMode(AutopilotMode::Auto);

    controller.setTargetHeading(0.0);

    controller.update();

    EXPECT_LT(driver.lastCommands.rudderSetPoint, 0.0);
}

TEST(AutopilotController, ZeroHeadingErrorProducesZeroRudderCommand)
{
    MockDriver driver;

    driver.driverState.heading = 50.0;

    AutopilotController controller(driver);

    controller.setMode(AutopilotMode::Auto);

    controller.setTargetHeading(50.0);

    controller.update();

    EXPECT_DOUBLE_EQ(driver.lastCommands.rudderSetPoint, 0.0);
}

TEST(AutopilotController, UpdateNotifiesObserver)
{
    MockDriver driver;
    MockObserver observer;

    AutopilotController controller(driver);

    controller.addObserver(&observer);

    controller.update();

    EXPECT_TRUE(observer.notified);
}

TEST(AutopilotController, ObserverReceivesUpdatedState)
{
    MockDriver driver;
    MockObserver observer;

    driver.driverState.heading = 75.0;

    AutopilotController controller(driver);

    controller.addObserver(&observer);

    controller.update();

    EXPECT_DOUBLE_EQ(observer.lastState.heading, 75.0);
}

TEST(AutopilotController, RemovedObserverIsNotNotified)
{
    MockDriver driver;
    MockObserver observer;

    AutopilotController controller(driver);

    controller.addObserver(&observer);
    controller.removeObserver(&observer);

    controller.update();

    EXPECT_FALSE(observer.notified);
}