#pragma once

#include <QObject>
#include <QTimer>

class SteeringViewModel;
class AutopilotController;

class QtSimulationDriver : public QObject
{
    Q_OBJECT

public:
    QtSimulationDriver(AutopilotController& controller,
                       SteeringViewModel& viewModel,
                       QObject* parent = nullptr);

private slots:
    void onTimeout();

private:
    AutopilotController& m_controller;
    SteeringViewModel& m_viewModel;

    QTimer m_timer;
};
