import QtQuick
import QtQuick.Effects

Item {
    id: root

    property real heading: 0
    property real displayedRotation: 0

    onHeadingChanged: {
        var target = -heading;
        var delta = target - displayedRotation;
        if (delta > 180)
            delta -= 360;
        else if (delta < -180)
            delta += 360;
        displayedRotation += delta;
    }

    implicitWidth: 320
    implicitHeight: 320

    Rectangle {
        anchors.fill: parent
        radius: width / 2

        color: "#455A64"

        border.width: 3
        border.color: "#90A4AE"
    }

    Rectangle {
        anchors.fill: parent
        anchors.margins: 6

        radius: width / 2

        color: "#263238"

        border.width: 2
        border.color: "#37474F"
    }

    Item {
        id: compassTicks
        anchors.fill: parent
        rotation: displayedRotation

        Behavior on rotation {
            NumberAnimation { duration: 250 }
        }

        Repeater {
            model: 36

            delegate: Rectangle {

                width: index % 3 === 0 ? 3 : 1
                height: index % 3 === 0 ? 16 : 8

                radius: 1
                color: "#CFD8DC"

                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 6

                transform: Rotation {
                    angle: index * 10
                    origin.x: width / 2
                    origin.y: compassTicks.height / 2 - 6
                }
            }
        }

        Repeater {
            model: 12

            delegate: Text {

                readonly property int angle: index * 30

                text: angle === 0 ? "360" : angle

                color: angle % 90 === 0 ? "white" : "#B0BEC5"
                font.pixelSize: angle % 90 === 0 ? 17 : 12
                font.bold: angle % 90 === 0

                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: root.height * 0.075

                transform: Rotation {
                    angle: index * 30
                    origin.x: width / 2
                    origin.y: compassTicks.height / 2 - root.height * 0.075
                }
            }
        }
    }

    Rectangle {
        id: centerDisc

        anchors.centerIn: parent

        width: parent.width * 0.54
        height: width

        radius: width / 2

        gradient: Gradient {
            GradientStop { position: 0.0; color: "#546E7A" }
            GradientStop { position: 1.0; color: "#263238" }
        }

        border.width: 2
        border.color: "#607D8B"
    }

    Item {
        id: compassCardinals

        anchors.fill: parent

        rotation: displayedRotation

        Behavior on rotation {
            NumberAnimation { duration: 250 }
        }

        Repeater {
            model: [
                { text: "N", angle: 0 },
                { text: "E", angle: 90 },
                { text: "S", angle: 180 },
                { text: "W", angle: 270 }
            ]

            delegate: Text {

                required property var modelData

                text: modelData.text

                color: modelData.text === "N" ? "#66BB6A" : "white"

                font.pixelSize: 22
                font.bold: true

                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: root.height * 0.15

                transform: Rotation {
                    angle: modelData.angle
                    origin.x: width / 2
                    origin.y: compassCardinals.height / 2 - root.height * 0.15
                }
            }
        }
    }

    Canvas {
        id: northArrow
        width: 20
        height: 28

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 16

        z: 30

        onPaint: {
            var ctx = getContext("2d");

            ctx.clearRect(0, 0, width, height);

            ctx.fillStyle = "#FF5252";

            ctx.strokeStyle = "#7F0000";
            ctx.lineWidth = 1;
            ctx.stroke();

            ctx.beginPath();
            ctx.moveTo(width / 2, 0);
            ctx.lineTo(width, height);
            ctx.lineTo(0, height);
            ctx.closePath();

            ctx.fill();
        }
    }

    Text {
        anchors.centerIn: centerDisc

        text: Number(root.heading).toFixed(1) + "°"

        color: "white"

        font.pixelSize: 30
        font.bold: true

        style: Text.Outline
        styleColor: "#111111"

        z: 5
    }

    MultiEffect {
        anchors.fill: centerDisc

        source: centerDisc

        shadowEnabled: true
        shadowBlur: 0.6
        shadowOpacity: 0.4
    }

    MultiEffect {
        anchors.fill: northArrow

        source: northArrow

        shadowEnabled: true
        shadowBlur: 0.6
        shadowOpacity: 0.4
    }

}