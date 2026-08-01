
#pragma once

#include <QObject>

#include "ControllerState.h"
#include "IAutopilotCommands.h"
#include "IControllerObserver.h"

class SteeringViewModel : public QObject, public IControllerObserver
{
    Q_OBJECT

    Q_PROPERTY(double heading READ heading NOTIFY headingChanged)
    Q_PROPERTY(double targetHeading READ targetHeading NOTIFY targetHeadingChanged)
    Q_PROPERTY(double rudderAngle READ rudderAngle NOTIFY rudderAngleChanged)

public:
    explicit SteeringViewModel(IAutopilotCommands& commands, QObject* parent = nullptr);

    Q_INVOKABLE void increaseTargetHeading();
    Q_INVOKABLE void decreaseTargetHeading();

    [[nodiscard]] auto heading() const -> double;
    [[nodiscard]] auto targetHeading() const -> double;
    [[nodiscard]] auto rudderAngle() const -> double;

    void onStateChanged(const ControllerState& state) override;

signals:
    void headingChanged();
    void targetHeadingChanged();
    void rudderAngleChanged();

private:
    [[nodiscard]] auto setHeading(double heading) -> bool;
    [[nodiscard]] auto setTargetHeading(double targetHeading) -> bool;
    [[nodiscard]] auto setRudderAngle(double rudderAngle) -> bool;

    IAutopilotCommands& m_commands;

    double m_heading = {};
    double m_targetHeading = {};
    double m_rudderAngle{};
};
