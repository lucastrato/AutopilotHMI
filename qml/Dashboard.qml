import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "components"

Rectangle {
    color: "#1E272C"

    readonly property int pageMargin: 24
    readonly property int sectionSpacing: 20
    readonly property int rowSpacing: 30
    readonly property int compassSize: 340
    readonly property int modeSelectorHeight: 60

    readonly property int instrumentWidth: 280
    readonly property int instrumentHeight: 160

    Item {
        id: dashboard

        anchors.centerIn: parent

        width: compassSize + rowSpacing + instrumentWidth
        height: compassSize + sectionSpacing + modeSelectorHeight

        ColumnLayout {
            anchors.fill: parent

            spacing: sectionSpacing

            RowLayout {
                Layout.fillWidth: true
                Layout.preferredHeight: compassSize

                spacing: rowSpacing

                Compass {
                    Layout.preferredWidth: compassSize
                    Layout.preferredHeight: compassSize

                    heading: steeringViewModel.heading
                }

                ColumnLayout {
                    //Layout.fillWidth: true

                    spacing: sectionSpacing

                    HeadingControl {

                        Layout.preferredWidth: instrumentWidth
                        Layout.preferredHeight: instrumentHeight

                        targetHeading: steeringViewModel.targetHeading

                        autoMode: steeringViewModel.isAuto

                        onMinus1Clicked:
                            steeringViewModel.decreaseTargetHeading()

                        onPlus1Clicked:
                            steeringViewModel.increaseTargetHeading()

                        onMinus10Clicked:
                            steeringViewModel.selectTargetHeading(steeringViewModel.targetHeading - 10)

                        onPlus10Clicked:
                            steeringViewModel.selectTargetHeading(steeringViewModel.targetHeading + 10)
                    }

                    RudderGauge {

                        Layout.preferredWidth: instrumentWidth
                        Layout.preferredHeight: instrumentHeight

                        rudderAngle: steeringViewModel.rudderAngle

                        manualMode: steeringViewModel.isManual

                        onMinus1Clicked:
                            steeringViewModel.decreaseRudder()

                        onPlus1Clicked:
                            steeringViewModel.increaseRudder()

                        onMinus10Clicked:
                            steeringViewModel.selectRudderAngle(steeringViewModel.rudderAngle - 10)

                        onPlus10Clicked:
                            steeringViewModel.selectRudderAngle(steeringViewModel.rudderAngle + 10)
                    }
                }
            }

            ModeSelector {

                Layout.fillWidth: true
                Layout.preferredHeight: modeSelectorHeight

                mode: steeringViewModel.mode

                onStandbyClicked:
                    steeringViewModel.setStandbyMode()

                onManualClicked:
                    steeringViewModel.setManualMode()

                onAutoClicked:
                    steeringViewModel.setAutoMode()
            }
        }

    }

}