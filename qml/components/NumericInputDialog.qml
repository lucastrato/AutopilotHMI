import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Popup {
    id: popup

    modal: true
    focus: true

    anchors.centerIn: Overlay.overlay

    width: 320
    height: 220

    closePolicy: Popup.NoAutoClose

    property string title: ""
    property real value: 0
    property string unit: ""
    signal accepted(real value)

    function openDialog(dialogTitle, dialogValue, dialogUnit, cb)
    {
        title = dialogTitle
        value = dialogValue
        unit = dialogUnit
        callback = cb

        editor.text = Number(dialogValue).toFixed(1)

        open()
    }

    background: Rectangle {
        radius: 12
        color: "#37474F"
        border.width: 2
        border.color: "#607D8B"
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20

        spacing: 18

        Text {
            Layout.alignment: Qt.AlignHCenter

            text: popup.title

            color: "white"

            font.pixelSize: 20
            font.bold: true
        }

        TextField {
            id: editor

            Layout.fillWidth: true

            horizontalAlignment: Text.AlignHCenter

            font.pixelSize: 30

            validator: DoubleValidator {}

            onAccepted: okButton.clicked()
        }

        Text {
            Layout.alignment: Qt.AlignHCenter

            text: popup.unit

            color: "#B0BEC5"

            font.pixelSize: 18
        }

        RowLayout {

            Layout.alignment: Qt.AlignHCenter

            spacing: 18

            NavButton {
                width: 70
                height: 36

                buttonText: "✕"

                onClicked: popup.close()
            }

            NavButton {
                id: okButton

                width: 70
                height: 36

                buttonText: "✓"

                onClicked: {
                    popup.accepted(Number(editor.text))
                    popup.close()
                }
            }
        }
    }

    onOpened: {
        editor.forceActiveFocus()
        editor.selectAll()
    }
}