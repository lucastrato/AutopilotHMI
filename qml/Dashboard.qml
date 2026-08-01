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
            title: "Target"
            value: steeringViewModel.targetHeading
            unit: "°"

            editable: true

            onIncreaseClicked: steeringViewModel.increaseTargetHeading()
            onDecreaseClicked: steeringViewModel.decreaseTargetHeading()
        }

        ValueCard {
            title: "Rudder"
            value: steeringViewModel.rudderAngle
            unit: "°"
        }

        ValueCard {
            title: "Mode"
            value: "AUTO"
        }
    }
}