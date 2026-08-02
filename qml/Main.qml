import QtQuick
import QtQuick.Controls

ApplicationWindow {

    readonly property real mainWindowWidth: 800
    readonly property real mainWindowHeight: 600

    width: mainWindowWidth
    height: mainWindowHeight
    visible: true

    title: "Marine Autopilot"

    Dashboard {
        anchors.fill: parent
    }
}