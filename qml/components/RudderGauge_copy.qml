import QtQuick
import QtQuick.Layouts

Item {
    id: root

    // Geometry
    readonly property int cornerRadius: 14

    readonly property real gaugeRadius: 85
    readonly property real gaugeCenterY: 0.72

    readonly property real indicatorRadius: 8
    readonly property real indicatorDistance: gaugeRadius

    readonly property real labelDistance: gaugeRadius + 20

    readonly property int majorTick: 12
    readonly property int minorTick: 7

    readonly property int tickWidth: 2
    readonly property int arcWidth: 4
    readonly property int innerArcWidth: 8

    readonly property int valueBottomMargin: 40
    readonly property int titleBottomMargin: 90

    readonly property int buttonSpacing: 30
    readonly property int buttonBottomMargin: 8
    readonly property int buttonWidth: 60
    readonly property int buttonHeight: 30

    readonly property int animationDuration: 200

    // Typography
    readonly property int labelFont: 12
    readonly property int valueFont: 30
    readonly property int unitFont: 18

    // Colours
    readonly property color backgroundTop: "#37474F"
    readonly property color backgroundBottom: "#263238"

    readonly property color borderColor: "#607D8B"

    readonly property color tickColor: "#ECEFF1"
    readonly property color arcColor: "#90A4AE"

    readonly property color textColor: "#ECEFF1"
    readonly property color secondaryText: "#B0BEC5"

    readonly property color indicatorColor: "#EF5350"
    readonly property color indicatorBorder: "#FFCDD2"

    property real rudderAngle: 0

    signal increaseClicked()
    signal decreaseClicked()

    implicitWidth: 320
    implicitHeight: 150

    Rectangle {
        anchors.fill: parent

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

        border.width: 1
        border.color: borderColor
    }

    Canvas {
        id: gauge

        anchors.fill: parent

        onPaint: {

            var ctx = getContext("2d")

            ctx.clearRect(0, 0, width, height)


            var cx = width / 2
            var cy = height * gaugeCenterY

            var radius = gaugeRadius


            // arc
            ctx.strokeStyle = arcColor
            ctx.lineWidth = arcWidth

            ctx.beginPath()

            ctx.arc(
                cx,
                cy,
                radius,
                Math.PI,
                2 * Math.PI
            )

            ctx.stroke()


            // ticks
            ctx.strokeStyle = textColor
            ctx.lineWidth = 2


            for (var angle = -35; angle <= 35; angle += 5) {

                var rad = Math.PI +
                          (angle + 35) / 70 * Math.PI


                var inner = radius - ((angle % 15 === 0) ? majorTick : minorTick)

                var x1 = cx + Math.cos(rad) * inner
                var y1 = cy + Math.sin(rad) * inner

                var x2 = cx + Math.cos(rad) * radius
                var y2 = cy + Math.sin(rad) * radius


                ctx.beginPath()

                ctx.moveTo(x1,y1)
                ctx.lineTo(x2,y2)

                ctx.stroke()
            }

            ctx.strokeStyle = backgroundTop
            ctx.lineWidth = innerArcWidth

            ctx.beginPath()

            ctx.arc(
                cx,
                cy,
                radius - 4,
                Math.PI,
                2 * Math.PI
            )

            ctx.stroke()
        }
    }


    Text {
        id: leftLabel

        text: "-35"

        color: "#CFD8DC"

        font.pixelSize: labelFont

        x: {
            var angle = -35
            var rad = Math.PI +
                      (angle + 35) / 70 * Math.PI

            return root.width / 2 +
                   Math.cos(rad) * 105 -
                   width / 2
        }

        y: {
            var angle = -35
            var rad = Math.PI +
                      (angle + 35) / 70 * Math.PI

            return root.height * 0.72 +
                   Math.sin(rad) * 105 -
                   height / 2
        }
    }


    Text {
        id: centerLabel

        text: "0"

        color: "#CFD8DC"

        font.pixelSize: labelFont

        x: parent.width / 2 - width / 2
        y: 35
    }


    Text {
        id: rightLabel

        text: "+35"

        color: "#CFD8DC"

        font.pixelSize: 12

        x: {
            var angle = 35
            var rad = Math.PI +
                      (angle + 35) / 70 * Math.PI

            return root.width / 2 +
                   Math.cos(rad) * 105 -
                   width / 2
        }

        y: {
            var angle = 35
            var rad = Math.PI +
                      (angle + 35) / 70 * Math.PI

            return root.height * 0.72 +
                   Math.sin(rad) * 105 -
                   height / 2
        }
    }

    // Moving indicator
    Rectangle {

        id: indicator

        width: 16
        height: 16
        radius: 8

        color: indicatorColor

        border.width: 1
        border.color: indicatorBorder

        layer.enabled: true

        x: {
            var angle = root.rudderAngle

            var rad = Math.PI +
                      (angle + 35) / 70 * Math.PI

            return root.width / 2 +
                   Math.cos(rad) * 85 -
                   width / 2
        }

        y: {
            var angle = root.rudderAngle

            var rad = Math.PI +
                      (angle + 35) / 70 * Math.PI

            return root.height * 0.72 +
                   Math.sin(rad) * 85 -
                   height / 2
        }


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
    }

    Text {
        width: parent.width

        horizontalAlignment: Text.AlignHCenter

        anchors.bottom: parent.bottom
        anchors.bottomMargin: titleBottomMargin

        text: "RUDDER"

        color: secondaryText

        font.pixelSize: labelFont
        font.bold: true
    }

    Item {

        width: valueText.width + unitText.width
        height: valueText.height
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: valueBottomMargin

        Text {
            id: valueText

            anchors.centerIn: parent

            text: Number(root.rudderAngle).toFixed(1)

            color: tickColor

            style: Text.Outline
            styleColor: backgroundTop

            font.pixelSize: valueFont
            font.bold: true
        }

        Text {
            id: unitText

            text: "°"

            color: tickColor

            style: Text.Outline
            styleColor: backgroundTop

            font.pixelSize: unitFont

            anchors.left: valueText.right
            anchors.top: valueText.top
            anchors.topMargin: 4
        }
    }

    Row {
        spacing: buttonSpacing

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: buttonBottomMargin


        NavButton {
            buttonText: "◀"
            enabled: root.enabled
            width: buttonWidth
            height: buttonHeight

            onClicked: root.decreaseClicked()
        }

        NavButton {
            buttonText: "▶"
            enabled: root.enabled
            width: buttonWidth
            height: buttonHeight

            onClicked: root.increaseClicked()
        }
    }
}