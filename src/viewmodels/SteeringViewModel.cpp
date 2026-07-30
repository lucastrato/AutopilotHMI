
#include "SteeringViewModel.h"

SteeringViewModel::SteeringViewModel(QObject *parent)
    : QObject(parent)
{

}

int SteeringViewModel::heading() const
{
    return m_heading;
}

void SteeringViewModel::setHeading(const int &heading)
{
    if (m_heading == heading)
        return;

    m_heading = heading;

    emit headingChanged();
}