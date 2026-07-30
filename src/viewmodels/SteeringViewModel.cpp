
#include "SteeringViewModel.h"

SteeringViewModel::SteeringViewModel(QObject *parent)
    : QObject(parent)
{
    connect(
        &m_timer, &QTimer::timeout,
        this,
        &SteeringViewModel::updateHeading);

    m_timer.start(1000);
}

QString SteeringViewModel::heading() const
{
    return m_heading;
}

void SteeringViewModel::setHeading(const QString &heading)
{
    if (m_heading == heading)
        return;

    m_heading = heading;

    emit headingChanged();
}

void SteeringViewModel::updateHeading()
{
    int heading = m_heading.toInt();

    heading = (heading + 1) % 360;

    setHeading(QString::number(heading));
}