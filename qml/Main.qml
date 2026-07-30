import QtQuick
import QtQuick.Controls

ApplicationWindow {
    width: 1024
    height: 600
    visible: true

    title: "Marine Autopilot"

    Dashboard {
        anchors.fill: parent
    }
}