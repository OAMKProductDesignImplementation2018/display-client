import QtQuick 2.0

Item {
    Rectangle {
        id: debugBox
        anchors.fill: parent

        border.color: "#000000"
        color: "#FFFFFF"

        Text {
            anchors.centerIn: parent
            font.pixelSize: 24
            text: "ToDo Notes Item"
            horizontalAlignment: Text.AlignHCenter
        }
    }
}
