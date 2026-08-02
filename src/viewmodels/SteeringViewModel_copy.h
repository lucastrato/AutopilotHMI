/**
 * @file SteeringViewModel.h
 * @brief ViewModel exposed to the QML user interface.
 *
 * The SteeringViewModel provides the interface between the C++ backend
 * and the QML frontend.
 *
 * It exposes:
 *  - current vessel information
 *  - target values selected by the operator
 *  - current autopilot mode
 *  - UI commands forwarded to the controller layer
 *
 * The ViewModel does not implement control algorithms.
 * It only translates UI actions into backend commands and publishes
 * backend state changes through Qt properties.
 */

#pragma once

#include <QObject>

#include "ControllerState.h"
#include "IAutopilotCommands.h"

/**
 * @class SteeringViewModel
 * @brief Qt ViewModel used by the QML steering interface.
 *
 * The class follows the Model-View-ViewModel (MVVM) pattern:
 *
 *      QML View
 *          |
 *          |
 * SteeringViewModel
 *          |
 *          |
 * AutopilotController
 *
 * Properties are exposed to QML using Q_PROPERTY and updated through
 * Qt signals whenever the backend state changes.
 */
class SteeringViewModel : public QObject
{
    Q_OBJECT

    /**
     * @brief Current vessel heading.
     *
     * Value received from the controller state.
     */
    Q_PROPERTY(double heading READ heading NOTIFY headingChanged)

    /**
     * @brief Selected target heading.
     *
     * Heading requested by the operator in AUTO mode.
     */
    Q_PROPERTY(double targetHeading READ targetHeading NOTIFY targetHeadingChanged)

    /**
     * @brief Current rudder angle.
     */
    Q_PROPERTY(double rudderAngle READ rudderAngle NOTIFY rudderAngleChanged)

    /**
     * @brief Current autopilot operating mode.
     */
    Q_PROPERTY(QString mode READ mode NOTIFY modeChanged)

    /**
     * @brief True when automatic steering is active.
     */
    Q_PROPERTY(bool isAuto READ isAuto NOTIFY modeChanged)

    /**
     * @brief True when manual steering is active.
     */
    Q_PROPERTY(bool isManual READ isManual NOTIFY modeChanged)

public:
    /**
     * @brief Creates the ViewModel.
     *
     * @param commands Interface used to send commands to the autopilot.
     * @param parent Qt parent object.
     */
    explicit SteeringViewModel(IAutopilotCommands& commands, QObject* parent = nullptr);

    /**
     * @brief Returns current heading.
     */
    double heading() const;

    /**
     * @brief Returns selected target heading.
     */
    double targetHeading() const;

    /**
     * @brief Returns current rudder angle.
     */
    double rudderAngle() const;

    /**
     * @brief Returns current operating mode.
     */
    QString mode() const;

    /**
     * @brief Returns whether AUTO mode is active.
     */
    bool isAuto() const;

    /**
     * @brief Returns whether MANUAL mode is active.
     */
    bool isManual() const;

public slots:

    /**
     * @brief Selects AUTO mode.
     */
    void setAutoMode();

    /**
     * @brief Selects MANUAL mode.
     */
    void setManualMode();

    /**
     * @brief Selects standby mode.
     */
    void setStandbyMode();

    /**
     * @brief Changes target heading.
     *
     * @param heading Desired heading in degrees.
     */
    void selectTargetHeading(double heading);

    /**
     * @brief Changes rudder command.
     *
     * @param angle Desired rudder angle.
     */
    void selectRudderAngle(double angle);

signals:

    /// Emitted when heading changes.
    void headingChanged();

    /// Emitted when target heading changes.
    void targetHeadingChanged();

    /// Emitted when rudder angle changes.
    void rudderAngleChanged();

    /// Emitted when autopilot mode changes.
    void modeChanged();

private:
    /**
     * @brief Updates properties from backend state.
     *
     * Called when new controller data is received.
     */
    void updateState(const ControllerState& state);

    /// Backend command interface.
    IAutopilotCommands& m_commands;

    /// Latest controller state.
    ControllerState m_state;
};