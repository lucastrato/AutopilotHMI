#include "AutopilotController.h"

AutopilotController::AutopilotController() = default;

int AutopilotController::heading() const
{
    return m_heading;
}

void AutopilotController::update()
{
    ++m_heading;

    if(m_heading > 359)
        m_heading = 0;
}
