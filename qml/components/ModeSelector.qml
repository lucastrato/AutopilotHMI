import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root

    property string mode: "Standby"

    signal standbyClicked()
    signal manualClicked()
    signal autoClicked()

    color: "#263238"
    radius: 10

    implicitWidth: 320
    implicitHeight: 80

    RowLayout {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 10

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            radius: 8
            color: root.mode === "Standby"
                   ? "#4CAF50"
                   : "#455A64"

            border.color: "#90A4AE"
            border.width: 1

            Text {
                anchors.centerIn: parent
                text: "STBY"
                color: "white"
                font.bold: true
            }

            MouseArea {
                anchors.fill: parent
                onClicked: root.standbyClicked()
            }
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            radius: 8
            color: root.mode === "Manual"
                   ? "#4CAF50"
                   : "#455A64"

            border.color: "#90A4AE"
            border.width: 1

            Text {
                anchors.centerIn: parent
                text: "MAN"
                color: "white"
                font.bold: true
            }

            MouseArea {
                anchors.fill: parent
                onClicked: root.manualClicked()
            }
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            radius: 8
            color: root.mode === "Auto"
                   ? "#4CAF50"
                   : "#455A64"

            border.color: "#90A4AE"
            border.width: 1

            Text {
                anchors.centerIn: parent
                text: "AUTO"
                color: "white"
                font.bold: true
            }

            MouseArea {
                anchors.fill: parent
                onClicked: root.autoClicked()
            }
        }
    }
}