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
                border.color: "#000000"

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
                border.color: "#000000"
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
        // x: root.width / 6
        // y: root.height / 14
        anchors.left: timesRoot.right
        anchors.right: parent.right
        anchors.top: daysRoot.bottom
        anchors.bottom: parent.bottom

        Column {
            Repeater {
                model: 13
                Rectangle {
                    color: "#F8F8FA"
                    border.color: "#000000"
                    width: tableRoot.width / 5
                    height: tableRoot.height / 13

                    Text {
                        anchors.centerIn: parent
                        text: monday[index] ? monday[index] : ""
                    }
                }
            }
        }

        Column {
            Repeater {
                model: 13

                Rectangle {
                    color: "#F8F8FA"
                    border.color: "#000000"
                    width: tableRoot.width / 5
                    height: tableRoot.height / 13

                    Text {
                        anchors.centerIn: parent
                        text: tuesday[index] ? tuesday[index] : ""
                    }
                }
            }
        }
        Column {
            Repeater {
                model: 13

                Rectangle {
                    color: "#F8F8FA"
                    border.color: "#000000"
                    width: tableRoot.width / 5
                    height: tableRoot.height / 13

                    Text {
                        anchors.centerIn: parent
                        text: wednesday[index] ? wednesday[index] : ""
                    }
                }
            }
        }
        Column {
            Repeater {
                model: 13

                Rectangle {
                    color: "#F8F8FA"
                    border.color: "#000000"
                    width: tableRoot.width / 5
                    height: tableRoot.height / 13

                    Text {
                        anchors.centerIn: parent
                        text: thursday[index] ? thursday[index] : ""
                    }
                }
            }
        }
        Column {
            Repeater {
                model: 13

                Rectangle {
                    color: "#F8F8FA"
                    border.color: "#000000"
                    width: tableRoot.width / 5
                    height: tableRoot.height / 13

                    Text {
                        anchors.centerIn: parent
                        text: friday[index] ? friday[index] : ""
                    }
                }
            }
        }
    }
}
