#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>

#include "src/viewmodels/SteeringViewModel.h"

int main(int argc, char *argv[])
{
    // Create the application
    QGuiApplication app(argc, argv);

    // Create the ViewModel before the QML engine so it outlives it
    SteeringViewModel steeringViewModel;

    // Create the QML engine
    QQmlApplicationEngine engine;

    // Exit the application if the root QML component fails to load.
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    // Expose ViewModel to QML
    engine.rootContext()->setContextProperty(
        "steeringViewModel",
        &steeringViewModel);

    // Load the module Main.qml from AutopilotHMI
    engine.loadFromModule("AutopilotHMI", "Main");

    return QGuiApplication::exec();
}
