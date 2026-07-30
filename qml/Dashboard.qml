import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "components"

Rectangle {

    color: "#263238"

    GridLayout {

        anchors.centerIn: parent

        columns: 2

        rowSpacing: 20
        columnSpacing: 20

        ValueCard {

            title: "Heading"
            value: "127"
            unit: "°"
        }

        ValueCard {

            title: "Target"
            value: "130"
            unit: "°"
        }

        ValueCard {

            title: "Rudder"
            value: "-8"
            unit: "°"
        }

        ValueCard {

            title: "Mode"
            value: "AUTO"
        }
    }
}
