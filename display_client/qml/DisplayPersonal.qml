import QtQuick 2.0

Item {
    id: root

    Rectangle {
        anchors.fill: parent
        color: "#F0F0F0"
        border.color: "#000000"
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
        id: topItem
        anchors.left: parent.left
        anchors.leftMargin: 50
        anchors.right: parent.right
        anchors.rightMargin: 50
        anchors.top: parent.top
        anchors.topMargin: (!dataUpdate.foodMenuVisible &&
                            !dataUpdate.notesVisible &&
                            !dataUpdate.newsVisible) ? 500 : dataUpdate.scheduleVisible ? 50 : 0
        height: dataUpdate.scheduleVisible ? 480 : 0

        Schedule {
            id: personalSchedule
            anchors.fill: parent
            visible: dataUpdate.scheduleVisible
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
        height: (dataUpdate.foodMenuVisible || dataUpdate.notesVisible) ? 480 : 0

        FoodMenu {
            id: personalFoodMenu
            anchors.left: parent.left
            anchors.right: dataUpdate.notesVisible ? parent.horizontalCenter : parent.right
            anchors.rightMargin: dataUpdate.notesVisible ? 10 : 0
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            visible: dataUpdate.foodMenuVisible
        }

        ToDoNotes {
            id: personalNotes
            anchors.left: dataUpdate.foodMenuVisible ? parent.horizontalCenter : parent.left
            anchors.leftMargin: dataUpdate.foodMenuVisible ? 10 : 0
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            visible: dataUpdate.notesVisible
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
        anchors.topMargin: dataUpdate.foodMenuVisible || dataUpdate.notesVisible ? 20 : 0
        height: dataUpdate.newsVisible ? 480 : 0

        News {
            id: personalNews
            anchors.fill: parent
            visible: dataUpdate.newsVisible
        }
    }
}
