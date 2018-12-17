import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Controls.Styles 1.4

Item {
    id: loadingItem
    width: parent.width
    height: parent.height

    visible: networkManager.waitingForApiToken

    Rectangle {
        width: parent.width
        height: parent.height
        anchors.fill: parent

        color: "white"

        Text {
            id: loadingText
            font.pixelSize: 48
            text: "Ladataan..."

            anchors.centerIn: parent
        }

        BusyIndicator {
            anchors.top: loadingText.bottom
            anchors.topMargin: 50
            anchors.horizontalCenter: parent.horizontalCenter

            width: loadingText.width / 2
            height: loadingText.width / 2

            running: loadingItem.visible
        }
    }
}
