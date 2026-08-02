import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "components"

Rectangle {
    color: "#1E272C"

    GridLayout {
        anchors.centerIn: parent

        columns: 2

        rowSpacing: 20
        columnSpacing: 20

        Compass {
            heading: steeringViewModel.heading
        }

        ValueCard {
            title: "Heading"

            value: steeringViewModel.targetHeading
            unit: "°"

            editable: true
            controlsEnabled: steeringViewModel.isAuto

            onIncreaseClicked: steeringViewModel.increaseTargetHeading()
            onDecreaseClicked: steeringViewModel.decreaseTargetHeading()
        }

        RudderGauge {

            rudderAngle: steeringViewModel.rudderAngle

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