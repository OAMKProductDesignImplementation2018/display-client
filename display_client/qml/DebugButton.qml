import QtQuick 2.0

Item {
    id: debugButton

    property string color: "#909090"
    property string borderColor: "#000000"
    property int borderWidth: 1
    property int radius: 1

    signal buttonPressed()

    MouseArea {
        anchors.fill: parent

        onReleased: {
            buttonPressed()
        }
    }

    Rectangle {
        anchors.fill: parent
        color: debugButton.color
        border.color: debugButton.borderColor
        border.width: debugButton.borderWidth
        radius: debugButton.radius
    }
}
