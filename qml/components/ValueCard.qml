import QtQuick
import QtQuick.Layouts

Rectangle {
    id: card

    property string title: ""
    property var value: 0
    property string unit: ""

    property bool editable: false
    property bool controlsEnabled: true

    signal increaseClicked()
    signal decreaseClicked()

    radius: 12

    color: "#37474F"

    border.width: 1
    border.color: "#546E7A"

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
        }

        Item {
            Layout.fillHeight: true
        }

        RowLayout {
            Layout.alignment: Qt.AlignHCenter

            spacing: 18

            visible: editable

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