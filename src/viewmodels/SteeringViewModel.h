
#pragma once

#include <QObject>

#include "ControllerState.h"
#include "DisplayState.h"
#include "IAutopilotCommands.h"
#include "IControllerObserver.h"

class SteeringViewModel : public QObject, public IControllerObserver
{
    Q_OBJECT

    Q_PROPERTY(double heading READ heading NOTIFY headingChanged)
    Q_PROPERTY(double targetHeading READ targetHeading NOTIFY targetHeadingChanged)
    Q_PROPERTY(double rudderAngle READ rudderAngle NOTIFY rudderAngleChanged)

    Q_PROPERTY(QString mode READ mode NOTIFY modeChanged)

    Q_PROPERTY(bool isStandby READ isStandby NOTIFY modeChanged)
    Q_PROPERTY(bool isManual READ isManual NOTIFY modeChanged)
    Q_PROPERTY(bool isAuto READ isAuto NOTIFY modeChanged)

public:
    explicit SteeringViewModel(IAutopilotCommands& commands, QObject* parent = nullptr);

    Q_INVOKABLE void increaseTargetHeading();
    Q_INVOKABLE void decreaseTargetHeading();

    Q_INVOKABLE void increaseRudder();
    Q_INVOKABLE void decreaseRudder();

    Q_INVOKABLE void setStandbyMode();
    Q_INVOKABLE void setManualMode();
    Q_INVOKABLE void setAutoMode();

    [[nodiscard]] auto heading() const -> double;
    [[nodiscard]] auto targetHeading() const -> double;
    [[nodiscard]] auto rudderAngle() const -> double;

    [[nodiscard]] auto mode() const -> QString;

    [[nodiscard]] auto isStandby() const -> bool;
    [[nodiscard]] auto isManual() const -> bool;
    [[nodiscard]] auto isAuto() const -> bool;

    void onStateChanged(const ControllerState& state) override;

signals:
    void headingChanged();
    void targetHeadingChanged();
    void rudderAngleChanged();
    void modeChanged();

private:
    [[nodiscard]] auto setHeading(double heading) -> bool;
    [[nodiscard]] auto setTargetHeading(double targetHeading) -> bool;
    [[nodiscard]] auto setRudderAngle(double rudderAngle) -> bool;
    [[nodiscard]] auto setMode(AutopilotMode mode) -> bool;

    IAutopilotCommands& m_commands;

    DisplayState m_displayState;
};
