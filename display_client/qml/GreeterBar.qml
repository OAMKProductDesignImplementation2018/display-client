import QtQuick 2.0

Item {
    width: parent.width - 100
    height: 40

    x: 50
    y: 50

    Rectangle {
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        border.color: "#E1E8F1"
        color: "transparent"

        width: parent.width * 0.3
        height: parent.height

        Text {
            font.pixelSize: 21
            text: "Organization name"
            color: "black"

            // Dynamic font size
            fontSizeMode: Text.Fit
            width: parent.width
            height: parent.height

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            anchors.centerIn: parent
        }
    }

    Rectangle {
        y: 0
        anchors.centerIn: parent
        border.color: "#E1E8F1"
        color: "transparent"

        width: parent.width * 0.3
        height: parent.height

        Text {
            font.pixelSize: 28
            font.bold: true
            text: "13:45"
            color: "black"

            // Dynamic font size
            fontSizeMode: Text.Fit
            width: parent.width
            height: parent.height

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            anchors.centerIn: parent
        }
    }

    Rectangle {
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        border.color: "#E1E8F1"
        color: "transparent"

        width: parent.width * 0.3
        height: parent.height

        Text {
            font.pixelSize: 21
            text: "13.11.2018"
            color: "black"

            // Dynamic font size
            fontSizeMode: Text.Fit
            width: parent.width
            height: parent.height

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            anchors.centerIn: parent
        }
    }
}