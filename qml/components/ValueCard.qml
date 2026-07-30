import QtQuick
import QtQuick.Controls

Rectangle {

    property string title: " "
    property string value: " "
    property string unit: " "

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
            text: value + unit
            color: "white"
            font.pixelSize: 34
            horizontalAlignment: Text.AlignHCenter
            width: parent.width
        }
    }
}
