import QtQuick 2.0

Item {
    id: root

    Rectangle {
        id: debugBox
        anchors.fill: parent

        border.color: "#000000"
        color: "#00000000"
    }

    property var times: ["8-9", "9-10", "10-11", "11-12",
                            "12-13", "13-14", "14-15", "15-16",
                            "16-17", "17-18", "18-19", "19-20", "20-21"]
    property var days: ["Mon", "Tue", "Wed", "Thu", "Fri"]

    property var monday: dataUpdate.scheduleMonday
    property var tuesday: dataUpdate.scheduleTuesday
    property var wednesday: dataUpdate.scheduleWednesday
    property var thursday: dataUpdate.scheduleThursday
    property var friday: dataUpdate.scheduleFriday

    property int cellWidth: tableRoot.width / 5
    property int cellHeight: tableRoot.height / 13

    property int mondayX: tableRoot.x
    property int tuesdayX: tableRoot.x + cellWidth
    property int wednesdayX: tableRoot.x + cellWidth * 2
    property int thursdayX: tableRoot.x + cellWidth * 3
    property int fridayX: tableRoot.x + cellWidth * 4

    // Convenience variables for positioning the events
    property int fifteenMinutes: cellHeight / 4
    property int thirtyMinutes: cellHeight / 2
    property int hour: cellHeight


    Row {
        id: daysRoot
        anchors.left: timesRoot.right
        anchors.right: parent.right

        Repeater {
            model: days
            Rectangle {
                width: daysRoot.width / 5
                height: root.height / 18
                color: "#00CCFF"
                border.color: "#5A5A5A"

                Text {
                    anchors.centerIn: parent
                    text: modelData
                }
            }
        }
    }

    Column {
        id: timesRoot
        x: 0
        anchors.top: daysRoot.bottom
        anchors.bottom: parent.bottom
        width: root.width / 9

        Repeater {
            model: times

            Rectangle {
                color: "#00CCFF"
                border.color: "#5A5A5A"
                width: root.width / 9
                height: timesRoot.height / 13

                Text {
                    anchors.centerIn: parent
                    color: "#000000"
                    text: modelData
                }
            }
        }
    }

    Row {
        id: tableRoot
        anchors.left: timesRoot.right
        anchors.top: daysRoot.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        Repeater {
            model: 5

            Column {
                Repeater {
                    model: 13
                    Rectangle {
                        width: tableRoot.width / 5      // Don't use cellHeight or cellWidth,
                        height: tableRoot.height / 13   // they won't round properly
                        color: "#FAFAFA"
                        border.color: "#000000"
                    }
                }
            }
        }
    }
}
