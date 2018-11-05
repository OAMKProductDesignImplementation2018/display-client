import QtQuick 2.0

Item {
    Rectangle {
        anchors.fill: parent
        color: "#B0B0B0"
        border.color: "#000000"
    }

    Schedule {
        x: 50
        y: 50
        width: 800
        height: 480
    }

    FoodMenu {
        x: 50
        y: 550
        width: 400
        height: 480
    }

    Advertisement {
        x: 480
        y: 550
        width: 370
        height: 480
    }

    News {
        x: 50
        y: 1050
        width: 800
        height: 300
    }
}
