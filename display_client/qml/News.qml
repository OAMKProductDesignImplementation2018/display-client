import QtQuick 2.0

Item {
    Rectangle {
        id: debugBox
        anchors.fill: parent

        border.color: "#000000"
        color: "#FFFFFF"

        Text {
            id: newsItemText
            anchors.centerIn: parent
            font.pixelSize: 24
            text: "News Item"
            horizontalAlignment: Text.AlignHCenter
        }
    }
}
