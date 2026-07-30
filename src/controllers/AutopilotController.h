#pragma once

class AutopilotController
{
public:
    AutopilotController();

    void update();

    int heading() const;

private:
    int m_heading = 127;
};
