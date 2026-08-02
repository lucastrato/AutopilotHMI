import QtQuick
import QtQuick.Layouts

Item {
    id: root

    //----------------------------------------------------
    // Public API
    //----------------------------------------------------

    property real rudderAngle: 0
    property bool manualMode: false

    signal minus10Clicked()
    signal minus1Clicked()
    signal plus1Clicked()
    signal plus10Clicked()

    //----------------------------------------------------
    // Layout
    //----------------------------------------------------

    implicitWidth: 320
    implicitHeight: 190

    readonly property real cornerRadius: height * 0.08

    readonly property real contentMargin: height * 0.038

    readonly property real titleFont: height * 0.1
    readonly property real valueFont: height * 0.20
    readonly property real unitFont: valueFont * 0.55

    readonly property real labelFont: height * 0.07

    readonly property real gaugeCenterY: height * 0.7
    readonly property real gaugeRadius: Math.min(width, height) * 0.42

    readonly property real majorTick: gaugeRadius * 0.16
    readonly property real minorTick: gaugeRadius * 0.10

    readonly property real indicatorDiameter: gaugeRadius * 0.18

    readonly property real buttonWidth: width * 0.14
    readonly property real buttonHeight: height * 0.15
    readonly property real buttonSpacing: width * 0.04

    //----------------------------------------------------
    // Background
    //----------------------------------------------------

    Rectangle {

        anchors.fill: parent

        radius: root.cornerRadius

        gradient: Gradient {

            GradientStop {
                position: 0
                color: "#455A64"
            }

            GradientStop {
                position: 1
                color: "#37474F"
            }
        }

        border.width: 1
        border.color: "#607D8B"
    }

    //----------------------------------------------------
    // Title
    //----------------------------------------------------

    Text {

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: root.contentMargin

        text: "RUDDER"

        color: "#B0BEC5"

        font.pixelSize: root.titleFont
        font.bold: true
    }

    //----------------------------------------------------
    // Gauge
    //----------------------------------------------------

    Canvas {
        id: gauge

        anchors.fill: parent

        onPaint: {

            var ctx = getContext("2d")

            ctx.clearRect(0,0,width,height)

            var cx = width / 2
            var cy = root.gaugeCenterY

            var radius = root.gaugeRadius

            //---------------------------------
            // Arc
            //---------------------------------

            ctx.strokeStyle = "#90A4AE"
            ctx.lineWidth = 4

            ctx.beginPath()

            ctx.arc(
                cx,
                cy,
                radius,
                Math.PI,
                2*Math.PI
            )

            ctx.stroke()

            //---------------------------------
            // Inner shadow arc
            //---------------------------------

            ctx.strokeStyle = "#37474F"
            ctx.lineWidth = 8

            ctx.beginPath()

            ctx.arc(
                cx,
                cy,
                radius - 4,
                Math.PI,
                2*Math.PI
            )

            ctx.stroke()

            //---------------------------------
            // Tick marks
            //---------------------------------

            ctx.strokeStyle = "#ECEFF1"
            ctx.lineWidth = 2

            for (var angle=-35; angle<=35; angle+=5) {

                var rad = Math.PI + (angle+35)/70*Math.PI

                var tick =
                        angle % 15 === 0
                        ? root.majorTick
                        : root.minorTick

                ctx.beginPath()

                ctx.moveTo(
                    cx + Math.cos(rad)*(radius-tick),
                    cy + Math.sin(rad)*(radius-tick)
                )

                ctx.lineTo(
                    cx + Math.cos(rad)*radius,
                    cy + Math.sin(rad)*radius
                )

                ctx.stroke()
            }
        }
    }

    //----------------------------------------------------
    // Scale Labels
    //----------------------------------------------------

    Repeater {

        model: [
            { text: "-35", angle: -35 },
            { text: "0", angle: 0 },
            { text: "+35", angle: 35 }
        ]

        delegate: Text {

            required property var modelData

            color: "#CFD8DC"

            font.pixelSize: root.labelFont
            font.bold: modelData.angle === 0

            text: modelData.text

            readonly property real rad:
                Math.PI + (modelData.angle + 35) / 70 * Math.PI

            x:
                root.width/2 +
                Math.cos(rad)*(root.gaugeRadius + 12)
                - width/2

            y:
                root.gaugeCenterY +
                Math.sin(rad)*(root.gaugeRadius + 12)
                - height/2
        }
    }

    //----------------------------------------------------
    // Rudder indicator
    //----------------------------------------------------

    Rectangle {

        id: indicator

        width: root.indicatorDiameter
        height: width

        radius: width/2

        color: "#EF5350"

        border.width: 1
        border.color: "#FFCDD2"

        opacity: root.manualMode ? 1 : 0.45

        readonly property real rad:
            Math.PI + (root.rudderAngle + 35) / 70 * Math.PI

        x:
            root.width/2 +
            Math.cos(rad)*root.gaugeRadius
            - width/2

        y:
            root.gaugeCenterY +
            Math.sin(rad)*root.gaugeRadius
            - height/2

        Behavior on x {
            NumberAnimation {
                duration: 200
            }
        }

        Behavior on y {
            NumberAnimation {
                duration: 200
            }
        }

        Behavior on opacity {
            NumberAnimation {
                duration: 150
            }
        }
    }

    //----------------------------------------------------
    // Value
    //----------------------------------------------------

    Item {

        anchors.horizontalCenter: parent.horizontalCenter

        y: root.gaugeCenterY - root.gaugeRadius * 0.5

        width: valueText.width + unitText.width
        height: valueText.height

        opacity: root.manualMode ? 1 : 0.45

        Behavior on opacity {
            NumberAnimation {
                duration: 150
            }
        }

        Text {

            id: valueText

            anchors.centerIn: parent

            text: Number(root.rudderAngle).toFixed(1)

            color: "#ECEFF1"

            font.pixelSize: root.valueFont
            font.bold: true

            style: Text.Outline
            styleColor: "#263238"
        }

        Text {

            id: unitText

            anchors.left: valueText.right
            anchors.top: valueText.top

            anchors.topMargin: root.unitFont * 0.2

            text: "°"

            color: "#ECEFF1"

            font.pixelSize: root.unitFont

            style: Text.Outline
            styleColor: "#263238"
        }
    }
    //----------------------------------------------------
    // Controls
    //----------------------------------------------------

    RowLayout {

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: root.contentMargin

        spacing: root.buttonSpacing

        NavButton {

            width: root.buttonWidth
            height: root.buttonHeight

            buttonText: "◀◀"

            enabled: root.manualMode

            onClicked: root.minus10Clicked()
        }

        NavButton {

            width: root.buttonWidth
            height: root.buttonHeight

            buttonText: "◀"

            enabled: root.manualMode

            onClicked: root.minus1Clicked()
        }

        NavButton {

            width: root.buttonWidth
            height: root.buttonHeight

            buttonText: "▶"

            enabled: root.manualMode

            onClicked: root.plus1Clicked()
        }

        NavButton {

            width: root.buttonWidth
            height: root.buttonHeight

            buttonText: "▶▶"

            enabled: root.manualMode

            onClicked: root.plus10Clicked()
        }
    }
}
