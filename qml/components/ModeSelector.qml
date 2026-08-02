import QtQuick
import QtQuick.Layouts

Rectangle {
    id: root

    property string mode: "Standby"

    signal standbyClicked()
    signal manualClicked()
    signal autoClicked()

    readonly property int cornerRadius: 12
    readonly property int borderWidth: 1
    readonly property int contentMargin: 4
    readonly property int buttonSpacing: 4

    readonly property color borderColor: "#607D8B"
    readonly property color backgroundTop: "#455A64"
    readonly property color backgroundBottom: "#37474F"

    readonly property color standbyColor: "#546E7A"
    readonly property color manualColor: "#FB8C00"
    readonly property color autoColor: "#42A5F5"

    implicitWidth: 320
    implicitHeight: 60

    radius: cornerRadius

    gradient: Gradient {
        GradientStop {
            position: 0.0
            color: backgroundTop
        }

        GradientStop {
            position: 1.0
            color: backgroundBottom
        }
    }

    border.width: borderWidth
    border.color: borderColor

    RowLayout {

        anchors.fill: parent
        anchors.margins: contentMargin

        spacing: buttonSpacing

        ModeButton {

            Layout.fillWidth: true
            Layout.fillHeight: true

            text: "STBY"

            active: root.mode === "Standby"
            activeColor: standbyColor

            onClicked: root.standbyClicked()
        }

        ModeButton {

            Layout.fillWidth: true
            Layout.fillHeight: true

            text: "MAN"

            active: root.mode === "Manual"
            activeColor: manualColor

            onClicked: root.manualClicked()
        }

        ModeButton {

            Layout.fillWidth: true
            Layout.fillHeight: true

            text: "AUTO"

            active: root.mode === "Auto"
            activeColor: autoColor

            onClicked: root.autoClicked()
        }
    }
}