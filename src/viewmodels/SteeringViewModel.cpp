#include <QDebug>
#include <cmath>

#include "SteeringViewModel.h"

SteeringViewModel::SteeringViewModel(IAutopilotCommands& commands, QObject* parent)
    : QObject(parent), m_commands(commands)
{
}

auto SteeringViewModel::heading() const -> double
{
    return m_displayState.heading;
    ;
}

auto SteeringViewModel::targetHeading() const -> double
{
    return m_displayState.targetHeading;
}

auto SteeringViewModel::rudderAngle() const -> double
{
    return m_displayState.rudderAngle;
}

auto SteeringViewModel::mode() const -> QString
{
    switch (m_displayState.mode)
    {
        case AutopilotMode::Standby:
            return "Standby";

        case AutopilotMode::Manual:
            return "Manual";

        case AutopilotMode::Auto:
            return "Auto";
    }

    return "Unknown";
}

void SteeringViewModel::onStateChanged(const ControllerState& state)
{
    bool changed = false;

    changed |= setHeading(state.heading);
    changed |= setTargetHeading(state.targetHeading);
    changed |= setRudderAngle(state.rudderAngle);
    changed |= setMode(state.mode);

    if (changed)
    {
        qDebug() << "ViewModel Updated";
    }
}

auto SteeringViewModel::setHeading(double heading) -> bool
{
    if (m_displayState.heading == heading)
    {
        return false;
    }

    m_displayState.heading = heading;

    emit headingChanged();

    return true;
}

auto SteeringViewModel::setTargetHeading(double targetHeading) -> bool
{
    if (m_displayState.targetHeading == targetHeading)
    {
        return false;
    }

    m_displayState.targetHeading = targetHeading;

    emit targetHeadingChanged();

    return true;
}

auto SteeringViewModel::setRudderAngle(double rudderAngle) -> bool
{
    if (m_displayState.rudderAngle == rudderAngle)
    {
        return false;
    }

    m_displayState.rudderAngle = rudderAngle;

    emit rudderAngleChanged();

    return true;
}

auto SteeringViewModel::setMode(AutopilotMode mode) -> bool
{
    if (m_displayState.mode == mode)
    {
        return false;
    }

    m_displayState.mode = mode;

    emit modeChanged();

    return true;
}

void SteeringViewModel::increaseTargetHeading()
{
    if (m_displayState.mode != AutopilotMode::Auto)
        return;

    const double targetHeading = std::round(m_displayState.targetHeading);

    m_commands.setTargetHeading(targetHeading + 1.0);
}

void SteeringViewModel::decreaseTargetHeading()
{
    if (m_displayState.mode != AutopilotMode::Auto)
        return;

    const double targetHeading = std::round(m_displayState.targetHeading);

    m_commands.setTargetHeading(targetHeading - 1.0);
}

void SteeringViewModel::increaseRudder()
{
    if (m_displayState.mode != AutopilotMode::Manual)
        return;

    const double rudder = std::round(m_displayState.rudderAngle);

    m_commands.setRudder(rudder + 1.0);
}

void SteeringViewModel::decreaseRudder()
{
    if (m_displayState.mode != AutopilotMode::Manual)
        return;

    const double rudder = std::round(m_displayState.rudderAngle);

    m_commands.setRudder(rudder - 1.0);
}

void SteeringViewModel::setStandbyMode()

{
    m_commands.setMode(AutopilotMode::Standby);
}

void SteeringViewModel::setManualMode()

{
    m_commands.setMode(AutopilotMode::Manual);
}

void SteeringViewModel::setAutoMode()

{
    m_commands.setMode(AutopilotMode::Auto);
}

auto SteeringViewModel::isStandby() const -> bool
{
    return m_displayState.mode == AutopilotMode::Standby;
}

auto SteeringViewModel::isManual() const -> bool
{
    return m_displayState.mode == AutopilotMode::Manual;
}

auto SteeringViewModel::isAuto() const -> bool
{
    return m_displayState.mode == AutopilotMode::Auto;
}
