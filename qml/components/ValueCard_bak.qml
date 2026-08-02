import QtQuick
import QtQuick.Layouts

Item {
    id: card

    property string title: ""
    property var value: 0
    property string unit: ""

    property bool editable: false
    property bool editableValue: false
    property bool controlsEnabled: true

    signal valueEditRequested()
    signal increaseClicked()
    signal decreaseClicked()

    implicitWidth: 320
    implicitHeight: 150

    Rectangle {
        anchors.fill: parent
        anchors.topMargin: 4
        anchors.leftMargin: 2
        anchors.rightMargin: -2
        anchors.bottomMargin: -2

        radius: 12

        color: "#000000"

        opacity: 0.18
    }

    Rectangle {
        anchors.fill: parent
        radius: 12

        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#455A64"
            }

            GradientStop {
                position: 1
                color: "#37474F"
            }
        }

        border.width: 1
        border.color: "#607D8B"

        antialiasing: true

        implicitWidth: 220
        implicitHeight: 150

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 14

            spacing: 0

            Text {
                Layout.alignment: Qt.AlignHCenter

                text: title.toUpperCase()

                color: "#B0BEC5"

                font.pixelSize: 13
                font.bold: true
            }

            Item {
                Layout.fillHeight: true
            }

            Item {
                Layout.alignment: Qt.AlignHCenter

                implicitWidth: valueText.width + unitText.width
                implicitHeight: valueText.height

                Text {
                    id: valueText

                    anchors.centerIn: parent

                    text: typeof card.value === "number"
                          ? Number(card.value).toFixed(1)
                          : card.value

                    color: "white"

                    font.pixelSize: 38
                    font.bold: true
                }

                Text {
                    id: unitText

                    text: card.unit

                    color: "#B0BEC5"

                    font.pixelSize: 18

                    anchors.left: valueText.right
                    anchors.top: valueText.top
                    anchors.topMargin: 4
                }

                MouseArea {
                    anchors.fill: parent

                    enabled: card.editableValue

                    cursorShape: enabled
                                 ? Qt.PointingHandCursor
                                 : Qt.ArrowCursor

                    onClicked: card.valueEditRequested()
                }
            }

            Item {
                Layout.fillHeight: true
                visible: editable
            }

            RowLayout {
                Layout.alignment: Qt.AlignHCenter
                visible: true
                spacing: 18

                NavButton {
                    buttonText: "−"

                    enabled: card.controlsEnabled
                    opacity: enabled ? 1.0 : 0.35

                    onClicked: card.decreaseClicked()
                }

                NavButton {
                    buttonText: "+"

                    enabled: card.controlsEnabled
                    opacity: enabled ? 1.0 : 0.35

                    onClicked: card.increaseClicked()
                }
            }
        }
    }
}