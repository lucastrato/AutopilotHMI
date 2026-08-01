#pragma once

#include <QObject>
#include <QTimer>

#include "DriverState.h"
#include "IControllerDriver.h"

class QtSimulationDriver : public QObject, public IControllerDriver
{
    Q_OBJECT

public:
    explicit QtSimulationDriver(QObject* parent = nullptr);

    [[nodiscard]] auto readState() -> DriverState override;

signals:
    void stateUpdated();

private slots:
    void onTimeout();

private:
    DriverState m_state;

    QTimer m_timer;
};
