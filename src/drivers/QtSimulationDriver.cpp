#include "QtSimulationDriver.h"
#include "Constants.h"

QtSimulationDriver::QtSimulationDriver(QObject* parent)
    : QObject(parent)
{
    connect(
        &m_timer, &QTimer::timeout,
        this,
        &QtSimulationDriver::onTimeout);

    m_timer.start(Constants::UiRefreshIntervalMs);
}

void QtSimulationDriver::onTimeout()
{
    //
    // Update simulated values
    //

    m_state.heading += 0.5;

    if (m_state.heading >= Constants::FullCircleDeg)
    {
        m_state.heading -= Constants::FullCircleDeg;
    }

    m_state.rudderAngle = std::sin(m_state.heading * 0.05) * 25.0;

    emit stateUpdated();
}

auto QtSimulationDriver::readState() -> DriverState
{
    return m_state;
}