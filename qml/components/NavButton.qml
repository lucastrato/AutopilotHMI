import QtQuick

Rectangle {
    id: root

    property bool enabled: true
    property string buttonText: ""

    signal clicked()

    readonly property int cornerRadius: 8
    readonly property int borderWidth: 1
    readonly property int innerMargin: 1

    readonly property real pressedScale: 0.92
    readonly property real disabledOpacity: 0.35

    readonly property int animationDuration: 80

    readonly property int textSize: 22
    readonly property int textVerticalOffset: -2

    readonly property color topColor: "#607D8B"
    readonly property color pressedTopColor: "#546E7A"
    readonly property color bottomColor: "#455A64"

    readonly property color borderColor: "#90A4AE"
    readonly property color innerBorderColor: "#263238"

    readonly property color textColor: "#ECEFF1"

    implicitWidth: 56
    implicitHeight: 30

    radius: cornerRadius

    gradient: Gradient {

        GradientStop {
            position: 0.0
            color: mouse.pressed ? pressedTopColor : topColor
        }

        GradientStop {
            position: 1.0
            color: bottomColor
        }
    }

    opacity: enabled ? 1.0 : disabledOpacity

    border.width: borderWidth
    border.color: borderColor

    scale: mouse.pressed ? pressedScale : 1.0

    Behavior on scale {
        NumberAnimation {
            duration: animationDuration
        }
    }

    Rectangle {

        anchors.fill: parent
        anchors.margins: innerMargin

        radius: cornerRadius - 1

        color: "transparent"

        border.width: borderWidth
        border.color: innerBorderColor

        opacity: disabledOpacity
    }

    Text {
        anchors.centerIn: parent

        anchors.verticalCenterOffset: textVerticalOffset

        text: root.buttonText

        color: textColor

        font.pixelSize: textSize
        font.bold: true

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    MouseArea {
        id: mouse

        anchors.fill: parent

        enabled: root.enabled

        cursorShape: enabled
                     ? Qt.PointingHandCursor
                     : Qt.ArrowCursor

        onClicked: root.clicked()
    }
}