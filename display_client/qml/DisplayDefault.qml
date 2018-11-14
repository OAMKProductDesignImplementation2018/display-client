import QtQuick 2.0

Item {
    Rectangle {
        anchors.fill: parent
        border.color: "#000000"

        gradient: Gradient {
            GradientStop { position: 0.0; color: "#EAEAEA" }
            GradientStop { position: 1.0; color: "#8A8A8A" }

        }
    }

    Item {
        id: greeterBar

        x: 50
        y: 50
        width: parent.width - 100
        height: 40

        Text {
            y: 0
            anchors.centerIn: parent
            text: "13:45"
            font.pixelSize: 28
        }

        Text {
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 21
            text: "13.11.2018"
            color: "#000000"
        }
    }

    Item {
        id: topItem
        anchors.left: parent.left
        anchors.leftMargin: 50
        anchors.right: parent.right
        anchors.rightMargin: 50
        anchors.top: greeterBar.bottom
        anchors.topMargin: 2
        height: 540

        Schedule {
            anchors.fill: parent
        }
    }

    Item {
        id: centerItem
        anchors.left: parent.left
        anchors.leftMargin: 50
        anchors.right: parent.right
        anchors.rightMargin: 50
        anchors.top: topItem.bottom
        anchors.topMargin: 20
        height: 480

        FoodMenu {
            anchors.left: parent.left
            anchors.right: parent.horizontalCenter
            anchors.rightMargin: 10
            anchors.top: parent.top
            anchors.bottom: parent.bottom
        }

        News {
            anchors.left: parent.horizontalCenter
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
        }
    }

    Item {
        id: bottomItem
        anchors.left: parent.left
        anchors.leftMargin: 50
        anchors.right: parent.right
        anchors.rightMargin: 50
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 50
        anchors.top: centerItem.bottom
        anchors.topMargin: 20

        Advertisement {
            anchors.fill: parent
        }
    }
}
