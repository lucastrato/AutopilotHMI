/**

* @file main.cpp
* @brief Entry point of the Autopilot HMI application.
*
* This file initializes the Qt application, creates the backend
* components, exposes them to the QML engine and starts the
* graphical user interface.
*
* Application flow:
*   1. Create the QGuiApplication.
*   2. Instantiate the SteeringViewModel.
*   3. Expose the ViewModel to QML.
*   4. Load the main QML interface.
*   5. Enter the Qt event loop.
 */

#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "AutopilotController.h"
#include "QtSimulationDriver.h"
#include "SteeringViewModel.h"

auto main(int argc, char* argv[]) -> int
{
    qDebug() << "Starting Autopilot...";

    // Qt application instance
    QGuiApplication app(argc, argv);

    QtSimulationDriver simDriver;

    AutopilotController controller(simDriver);

    // Create the ViewModel before the QML engine so it outlives it
    SteeringViewModel steeringViewModel(controller);

    // Register the ViewModel as observer
    controller.addObserver(&steeringViewModel);

    QObject::connect(&simDriver, &QtSimulationDriver::stateUpdated,
                     [&controller]() -> void { controller.update(); });

    QQmlApplicationEngine engine;

    // Exit the application if the root QML component fails to load.
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreationFailed, &app,
        []() -> void { QCoreApplication::exit(-1); }, Qt::QueuedConnection);

    // Expose ViewModel to QML
    engine.rootContext()->setContextProperty("steeringViewModel", &steeringViewModel);

    // Load the module Main.qml from AutopilotHMI
    engine.loadFromModule("AutopilotHMI", "Main");

    return QGuiApplication::exec();
}
