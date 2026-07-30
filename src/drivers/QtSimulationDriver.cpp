#include "QtSimulationDriver.h"

#include "../controllers/AutopilotController.h"
#include "../viewmodels/SteeringViewModel.h"


QtSimulationDriver::QtSimulationDriver(
    AutopilotController& controller,
    SteeringViewModel& viewModel,
    QObject* parent)
    : QObject(parent)
    , m_controller(controller)
    , m_viewModel(viewModel)
{
    connect(
        &m_timer, &QTimer::timeout,
        this,
        &QtSimulationDriver::onTimeout);

    m_timer.start(1000);
}

void QtSimulationDriver::onTimeout()
{
    m_controller.update();

    m_viewModel.setHeading(m_controller.heading());
}
