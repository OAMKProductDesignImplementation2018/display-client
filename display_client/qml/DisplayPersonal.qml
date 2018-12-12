import QtQuick 2.0

Item {
    id: root

    Rectangle {
        anchors.fill: parent
        border.color: "#000000"

        color: "white"
    }

    GreeterBar {
        id: greeterBar
    }

    Item {
        id: topItem
        anchors.left: parent.left
        anchors.leftMargin: 50
        anchors.right: parent.right
        anchors.rightMargin: 50
        anchors.top: greeterBar.bottom
        anchors.topMargin: 10
        height: dataUpdate.scheduleVisible ? (!dataUpdate.foodMenuVisible && !dataUpdate.newsVisible) ? 1270 : 760 : 0

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
        anchors.topMargin: dataUpdate.scheduleVisible ? 20 : 0
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
