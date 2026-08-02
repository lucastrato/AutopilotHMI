import QtQuick

Rectangle {
    id: root

    property string text: ""
    property bool active: false
    property color activeColor: "#42A5F5"

    readonly property int buttonRadius: 8
    readonly property int buttonFontSize: 14

    signal clicked()

    radius: buttonRadius

    color: active ? activeColor : "#37474F"

    border.width: 1
    border.color: active ? Qt.lighter(activeColor, 1.3) : "#546E7A"

    Behavior on color {
        ColorAnimation { duration: 180 }
    }

    Behavior on border.color {
        ColorAnimation { duration: 180 }
    }

    Text {
        anchors.centerIn: parent

        text: root.text

        color: "white"

        font.pixelSize: buttonFontSize
        font.bold: true
    }

    MouseArea {
        anchors.fill: parent

        onClicked: root.clicked()
    }
}