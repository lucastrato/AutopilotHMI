import QtQuick
import QtQuick.Layouts

Item {
    id: root

    property real targetHeading: 0
    property bool autoMode: false
    property int contentMargin: 8

    property int buttonSpacing: 10
    property int bottomSpacing: 14

    readonly property real cornerRadius: height * 0.08

    readonly property real titleFont: height * 0.1
    readonly property real valueFont: height * 0.25
    readonly property real subtitleFont: height * 0.1

    readonly property real buttonWidth: width * 0.13
    readonly property real buttonHeight: height * 0.15

    signal minus10Clicked()
    signal minus1Clicked()
    signal plus1Clicked()
    signal plus10Clicked()

    implicitWidth: 320
    implicitHeight: 170

    Rectangle {
        anchors.fill: parent

        radius: root.cornerRadius

        gradient: Gradient {
            GradientStop { position: 0.0; color: "#455A64" }
            GradientStop { position: 1.0; color: "#37474F" }
        }

        border.width: 1
        border.color: "#607D8B"
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: root.contentMargin

        spacing: height * 0.05

        Text {
            Layout.alignment: Qt.AlignHCenter

            text: "HEADING"

            color: "#B0BEC5"

            font.pixelSize: root.titleFont
            font.bold: true
        }

        Item {

            Layout.fillWidth: true
            height: valueText.height

            Text {
                id: valueText

                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter

                text: Number(root.targetHeading).toFixed(1)

                font.pixelSize: root.valueFont
                font.bold: true

                color: "#ECEFF1"

                style: Text.Outline
                styleColor: "#263238"
            }

            Text {
                id: unitText

                text: "°"

                font.pixelSize: root.valueFont * 0.45

                color: "#ECEFF1"

                anchors.left: valueText.right
                anchors.leftMargin: root.valueFont * 0.03

                anchors.top: valueText.top
                anchors.topMargin: root.valueFont * 0.10
            }
        }

        Text {
            Layout.alignment: Qt.AlignHCenter

            text: "Selected Course"

            color: "#90A4AE"

            font.pixelSize: root.subtitleFont
        }

        Item {
            Layout.fillHeight: true
        }

        RowLayout {

            Layout.alignment: Qt.AlignHCenter

            Layout.bottomMargin: root.bottomSpacing

            spacing: root.buttonSpacing

            NavButton {
                width: root.buttonWidth
                height: root.buttonHeight

                buttonText: "◀◀"

                enabled: root.autoMode

                onClicked: root.minus10Clicked()
            }

            NavButton {
                width: root.buttonWidth
                height: root.buttonHeight

                buttonText: "◀"

                enabled: root.autoMode

                onClicked: root.minus1Clicked()
            }

            NavButton {
                width: root.buttonWidth
                height: root.buttonHeight

                buttonText: "▶"

                enabled: root.autoMode

                onClicked: root.plus1Clicked()
            }

            NavButton {
                width: root.buttonWidth
                height: root.buttonHeight

                buttonText: "▶▶"

                enabled: root.autoMode

                onClicked: root.plus10Clicked()
            }
        }
    }
}