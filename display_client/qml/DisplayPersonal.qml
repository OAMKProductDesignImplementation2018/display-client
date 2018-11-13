import QtQuick 2.0

Item {
    id: root

    Rectangle {
        anchors.fill: parent
        border.color: "#000000"

        gradient: Gradient {
            GradientStop { position: 0.0; color: "#FAFAFA" }
            GradientStop { position: 1.0; color: "#f5deb3" }

        }
    }

    Connections {
        target: dataUpdate
        onScheduleVisibleChanged: {

        }

        onFoodMenuVisibleChanged: {

        }

        onNotesVisibleChanged: {

        }

        onNewsVisibleChanged: {

        }
    }

    Item {
        id: greeterText

        x: 50
        y: 50
        width: parent.width - 100
        height: 50

        Text {
            anchors.left: parent.left
            font.pixelSize: 21
            text: "Hello, " + dataUpdate.firstName + "!"
        }

        Text {
            anchors.right: parent.right
            font.pixelSize: 21
            text: "13.11.2018" + "   " +  "13:45"
            color: "#FF0000"
        }
    }

    Item {
        id: topItem
        anchors.left: parent.left
        anchors.leftMargin: 50
        anchors.right: parent.right
        anchors.rightMargin: 50
        anchors.top: parent.top
        anchors.topMargin: dataUpdate.scheduleVisible ? 85 : 0
        height: dataUpdate.scheduleVisible ? (!dataUpdate.foodMenuVisible && !dataUpdate.newsVisible) ? 1312 : 760 : 0

        Schedule {
            id: personalSchedule
            anchors.fill: parent
            visible: dataUpdate.scheduleVisible
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
        anchors.top: topItem.bottom
        anchors.topMargin: dataUpdate.foodMenuVisible || dataUpdate.newsVisible ? 20 : 0
        height: dataUpdate.newsVisible || dataUpdate.foodMenuVisible ? 480 : 0

        FoodMenu {
            id: personalFoodMenu
            anchors.left: parent.left
            anchors.right: dataUpdate.newsVisible ? parent.horizontalCenter : parent.right
            anchors.rightMargin: dataUpdate.newsVisible ? 10 : 0
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            visible: dataUpdate.foodMenuVisible
        }

        News {
            id: personalNews
            anchors.left: dataUpdate.foodMenuVisible ? parent.horizontalCenter : parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            visible: dataUpdate.newsVisible
        }
    }
}
