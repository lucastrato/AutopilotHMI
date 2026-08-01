#pragma once

class IAutopilotCommands
{
public:
    virtual ~IAutopilotCommands() = default;

    virtual void increaseTargetHeading() = 0;
    virtual void decreaseTargetHeading() = 0;
};