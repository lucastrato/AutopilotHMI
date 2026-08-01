import QtQuick
import QtQuick.Controls

Rectangle {
    id: root

    property string title: " "
    property var value: " "
    property string unit: " "

    property bool editable: false
    property bool enabled: true

    signal increaseClicked()
    signal decreaseClicked()

    radius: 8
    color: "#37474F"

    implicitWidth: 220
    implicitHeight: 120

    Column {
        anchors.centerIn: parent
        width: parent.width - 20
        spacing: 6

        Label {
            text: title
            color: "lightgray"
            font.pixelSize: 18
            horizontalAlignment: Text.AlignHCenter
            width: parent.width
        }

        Label {
            text: typeof value === "number"
                ? Number(value).toFixed(1) + unit
                : value
            color: "white"
            font.pixelSize: 34
            horizontalAlignment: Text.AlignHCenter
            width: parent.width
        }

        Row {
            visible: editable
            enabled: parent.enabled

            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 10

            Button {
                text: "-"
                visible: editable
                enabled: editable && root.enabled
                onClicked: decreaseClicked()
            }

            Button {
                text: "+"
                visible: editable
                enabled: editable && root.enabled
                onClicked: increaseClicked()
            }
        }
    }
}
