#pragma once

#include <QObject>
#include <QTimer>

#include "IControllerDriver.h"

class QtSimulationDriver : public QObject, public IControllerDriver
{
    Q_OBJECT

public:
    explicit QtSimulationDriver(QObject* parent = nullptr);

    [[nodiscard]] auto readState() -> DriverState override;

    void writeCommands(const DriverCommands& commands) override;

signals:
    void stateUpdated();

private slots:
    void onTimeout();

private:
    DriverState m_state;
    DriverCommands m_commands;

    QTimer m_timer;
};
