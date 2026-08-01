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

    // Create the application
    QGuiApplication app(argc, argv);

    // Create Sim Driver
    QtSimulationDriver simDriver;

    // Create the AutopilotController
    AutopilotController controller(simDriver);

    // Create the ViewModel before the QML engine so it outlives it
    SteeringViewModel steeringViewModel(controller);
    // Connect the simulation to the controller

    // Register the ViewModel as observer
    controller.addObserver(&steeringViewModel);

    QObject::connect(&simDriver, &QtSimulationDriver::stateUpdated,
                     [&controller]() -> void { controller.update(); });

    // Create the QML engine
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
