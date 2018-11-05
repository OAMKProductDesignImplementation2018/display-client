import QtQuick 2.0

Item {

    Rectangle {
        anchors.fill: parent
        color: "#F0F0F0"
        border.color: "#000000"
    }

    Schedule {
        id: personalSchedule
        x: 50
        y: 50
        width: 800
        height: 480
        visible: dataUpdate.scheduleVisible
    }

    FoodMenu {
        x: 50
        y: 550
        width: 400
        height: 480
        visible: dataUpdate.foodMenuVisible
    }

    News {
        x: 50
        y: 1050
        width: 800
        height: 300
        visible: dataUpdate.newsVisible
    }

    ToDoNotes {
        x: 480
        y: 550
        width: 370
        height: 480
        visible: dataUpdate.notesVisible
    }
}
