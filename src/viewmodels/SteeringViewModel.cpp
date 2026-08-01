#include <QDebug>

#include "SteeringViewModel.h"

SteeringViewModel::SteeringViewModel(IAutopilotCommands& commands, QObject* parent)
    : QObject(parent), m_commands(commands)
{
}

auto SteeringViewModel::heading() const -> double
{
    return m_heading;
}

auto SteeringViewModel::targetHeading() const -> double
{
    return m_targetHeading;
}

auto SteeringViewModel::rudderAngle() const -> double
{
    return m_rudderAngle;
}

void SteeringViewModel::onStateChanged(const ControllerState& state)
{
    bool changed = false;

    changed |= setHeading(state.heading);
    changed |= setTargetHeading(state.targetHeading);
    changed |= setRudderAngle(state.rudderAngle);

    if (changed)
    {
        qDebug() << "ViewModel Updated";
    }
}

auto SteeringViewModel::setHeading(double heading) -> bool
{
    if (m_heading == heading)
    {
        return false;
    }

    m_heading = heading;

    emit headingChanged();

    return true;
}

auto SteeringViewModel::setTargetHeading(double targetHeading) -> bool
{
    if (m_targetHeading == targetHeading)
    {
        return false;
    }

    m_targetHeading = targetHeading;

    emit targetHeadingChanged();

    return true;
}

auto SteeringViewModel::setRudderAngle(double rudderAngle) -> bool
{
    if (m_rudderAngle == rudderAngle)
    {
        return false;
    }

    m_rudderAngle = rudderAngle;

    emit rudderAngleChanged();

    return true;
}

void SteeringViewModel::increaseTargetHeading()
{
    m_commands.increaseTargetHeading();
}

void SteeringViewModel::decreaseTargetHeading()
{
    m_commands.decreaseTargetHeading();
}
