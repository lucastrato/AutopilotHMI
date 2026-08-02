import QtQuick

Rectangle {
    id: root

    property bool enabled: true
    property string buttonText: ""

    signal clicked()

    width: 50
    height: 34

    radius: 8

    color:
        !enabled ? "#37474F"
      : mouse.pressed ? "#607D8B"
      : "#455A64"

    border.width: 1
    border.color: "#607D8B"

    scale: mouse.pressed ? 0.92 : 1.0

    Behavior on scale {
        NumberAnimation {
            duration: 80
        }
    }

    Text {
        anchors.centerIn: parent

        text: root.buttonText

        color: "white"

        font.pixelSize: 20
        font.bold: true
    }

    MouseArea {
        id: mouse

        anchors.fill: parent

        enabled: root.enabled

        cursorShape: enabled ? Qt.PointingHandCursor : Qt.ArrowCursor

        onClicked: root.clicked()
    }
}