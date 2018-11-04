import QtQuick 2.7
import QtQuick.Window 2.2

import TestClass 0.1

Window {
    id: mainWindowRoot
    visible: true
    width: 1600
    height: 900
    flags: Qt.FramelessWindowHint
    visibility: Window.Windowed

    Component.onCompleted: {
        setX(Screen.width / 2 - width / 2)
        setY(Screen.height / 2 - height / 2)
    }

    Item {
        id: mainWindow
        anchors.fill: parent

        // Qt Classes

        TestClass { id: testClass }

        Item {
            id: background
            anchors.fill: parent

            Rectangle {
                anchors.fill: parent
                color: "#F0F0F0"
                border.color: "#000000"
                border.width: 1
            }
        }

        DebugButton {
            id: quitButton
            anchors.left: parent.left
            anchors.top: parent.top

            radius: 2
            color: "#909090"
            borderColor: "#000000"
            borderWidth: 1

            width: 50
            height: 50

            Text {
                anchors.centerIn: parent
                text: "X"
                font.pixelSize: 32
            }

            onButtonPressed: {
                Qt.quit()
            }
        }

        // Camera feed for debugging
        WebcamFeed {
            id: webcamFeed

            width: 800
            height: 600

            anchors.left: quitButton.right
            anchors.top: parent.top
        }

        DataDisplay {
            anchors.fill: parent
        }
    }
}
