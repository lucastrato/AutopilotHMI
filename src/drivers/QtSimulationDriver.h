/**
 * @file QtSimulationDriver.h
 * @brief ViewModel exposed to the QML user interface.
 *
 * Contains the QtSimulationDriver class used to simulate input/output data
 * the sensors/actuators
 */

#pragma once

#include <QObject>
#include <QTimer>

#include "IControllerDriver.h"

/**
 * @class QtSimulationDriver
 * @brief Qt-based simulation implementation of the controller driver.
 *
 * QtSimulationDriver provides a simulated implementation of the
 * IControllerDriver interface for testing and development purposes.
 *
 */
class QtSimulationDriver : public QObject, public IControllerDriver
{
    Q_OBJECT

public:
    explicit QtSimulationDriver(QObject* parent = nullptr);

    [[nodiscard]] auto readState() -> DriverState override;

    void writeCommands(const DriverCommands& commands) override;

signals:

    /**
     * @brief Emitted when the simulated driver state has been updated.
     *
     * This signal can be connected to controller or UI components that need
     * to react to new driver feedback.
     */
    void stateUpdated();

private slots:

    /**
     * @brief Timer callback used to update the simulation.
     *
     * Periodically advances the simulated system state based on the current
     * commands.
     */
    void onTimeout();

private:
    DriverState m_state;
    DriverCommands m_commands;
    QTimer m_timer;
};