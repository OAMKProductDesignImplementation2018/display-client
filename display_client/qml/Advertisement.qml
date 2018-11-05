import QtQuick 2.0

Item {
    Rectangle {
        anchors.fill: parent

        border.color: "#000000"
        color: "#FFFFFF"

        Text {
            anchors.centerIn: parent
            font.pixelSize: 24
            text: "Advertisement Item"
            horizontalAlignment: Text.AlignHCenter
        }
    }
}
