#include <QDebug>

#include "Constants.h"
#include "QtSimulationDriver.h"

QtSimulationDriver::QtSimulationDriver(QObject* parent) : QObject(parent)
{
    connect(&m_timer, &QTimer::timeout, this, &QtSimulationDriver::onTimeout);

    m_timer.start(Constants::SimulationUpdateIntervalMs);
}

void QtSimulationDriver::onTimeout()
{
    //
    // Update simulated values
    //

    m_state.heading += m_state.rudderAngle * Constants::HeadingRateGain;

    if (m_state.heading >= Constants::FullCircleDeg)
    {
        m_state.heading -= Constants::FullCircleDeg;
    }

    m_state.rudderAngle += (m_commands.rudderSetPoint - m_state.rudderAngle) * 0.2;

    emit stateUpdated();
}

auto QtSimulationDriver::readState() -> DriverState
{
    return m_state;
}

void QtSimulationDriver::writeCommands(const DriverCommands& commands)
{
    qDebug() << "Rudder setpoint:" << commands.rudderSetPoint;

    m_commands = commands;
}