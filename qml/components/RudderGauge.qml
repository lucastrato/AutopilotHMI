import QtQuick
import QtQuick.Layouts

Item {
    id: root

    property real rudderAngle: 0

    signal increaseClicked()
    signal decreaseClicked()

    implicitWidth: 260
    implicitHeight: 150

    Rectangle {
        anchors.fill: parent

        radius: 14

        gradient: Gradient {

            GradientStop {
                position: 0.0
                color: "#37474F"
            }

            GradientStop {
                position: 1.0
                color: "#263238"
            }
        }

        border.width: 1
        border.color: "#607D8B"
    }

    Canvas {
        id: gauge

        anchors.fill: parent

        onPaint: {

            var ctx = getContext("2d")

            ctx.clearRect(0, 0, width, height)


            var cx = width / 2
            var cy = height * 0.72

            var radius = 85


            // arc
            ctx.strokeStyle = "#90A4AE"
            ctx.lineWidth = 4

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
            ctx.strokeStyle = "#ECEFF1"
            ctx.lineWidth = 2


            for (var angle = -35; angle <= 35; angle += 5) {

                var rad = Math.PI +
                          (angle + 35) / 70 * Math.PI


                var inner = radius - ((angle % 15 === 0) ? 12 : 7)

                var x1 = cx + Math.cos(rad) * inner
                var y1 = cy + Math.sin(rad) * inner

                var x2 = cx + Math.cos(rad) * radius
                var y2 = cy + Math.sin(rad) * radius


                ctx.beginPath()

                ctx.moveTo(x1,y1)
                ctx.lineTo(x2,y2)

                ctx.stroke()
            }

            ctx.strokeStyle = "#37474F"
            ctx.lineWidth = 8

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

        font.pixelSize: 12

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

        font.pixelSize: 12

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

        color: "#EF5350"

        border.width: 1

        border.color: "#FFCDD2"

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
        anchors.bottomMargin: 80

        text: "RUDDER"

        color: "#B0BEC5"

        font.pixelSize: 12
        font.bold: true
    }

    Item {

        width: valueText.width + unitText.width
        height: valueText.height
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 45

        Text {
            id: valueText

            anchors.centerIn: parent

            text: Number(root.rudderAngle).toFixed(1)

            color: "#ECEFF1"

            style: Text.Outline
            styleColor: "#37474F"

            font.pixelSize: 30
            font.bold: true
        }

        Text {
            id: unitText

            text: "°"

            color: "#ECEFF1"

            style: Text.Outline
            styleColor: "#37474F"

            font.pixelSize: 18

            anchors.left: valueText.right
            anchors.top: valueText.top
            anchors.topMargin: 4
        }
    }

    Row {
        spacing: 40

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 12


        NavButton {
            buttonText: "−"

            width: 50
            height: 25

            onClicked: root.decreaseClicked()
        }


        NavButton {
            buttonText: "+"

            width: 50
            height: 25

            onClicked: root.increaseClicked()
        }
    }
}