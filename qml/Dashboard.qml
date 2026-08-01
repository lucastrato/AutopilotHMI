import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "components"

Rectangle {
    color: "#263238"

    GridLayout {
        anchors.centerIn: parent

        columns: 2
        rowSpacing: 20
        columnSpacing: 20

        ValueCard {
            title: "Heading"
            value: steeringViewModel.heading
            unit: "°"
        }

        ValueCard {
            title: "Target Heading"
            value: steeringViewModel.targetHeading
            unit: "°"

            editable: true
            enabled: steeringViewModel.isAuto

            onIncreaseClicked: steeringViewModel.increaseTargetHeading()
            onDecreaseClicked: steeringViewModel.decreaseTargetHeading()
        }

        ValueCard {
            title: "Rudder"
            value: steeringViewModel.rudderAngle
            unit: "°"

            editable: true
            enabled: steeringViewModel.isManual

            onIncreaseClicked:
                steeringViewModel.increaseRudder()

            onDecreaseClicked:
                steeringViewModel.decreaseRudder()
        }

        ModeSelector {

            mode: steeringViewModel.mode

            onStandbyClicked: steeringViewModel.setStandbyMode()

            onManualClicked: steeringViewModel.setManualMode()

            onAutoClicked: steeringViewModel.setAutoMode()
        }
    }
}