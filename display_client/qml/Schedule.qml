import QtQuick 2.0

Item {
    id: root

    Connections {
        target: dataUpdate

        // onNewScheduleEvent: {
        // tableRoot.createEvent(...)
    }

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

    property int firstHour: 8 // i.e. schedule starts at 8)

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

    DebugButton {
        x: 0
        y: 0
        width: 40
        height: 20

        color: "#FF0000"

        onButtonPressed: {
            tableRoot.createEvent("Wed", 17, 30, 19, 00, "Course name", "Teacher", "Room")
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

    Item {
        id: tableRoot

        anchors.left: timesRoot.right
        anchors.right: parent.right
        anchors.top: daysRoot.bottom
        anchors.bottom: parent.bottom

        function createEvent(day, startH, startM, endH, endM,
                             name, teacher, room)
        {
            var component = Qt.createComponent("ComponentEvent.qml")
            var sprite = component.createObject(tableRoot,
                                                {   "x": getX(day),
                                                    "y": getY(startH, startM),
                                                    "width": tableRoot.width / 5,
                                                    "height": getHeight(startH, startM, endH, endM),
                                                    "courseName": name,
                                                    "teacherName": teacher,
                                                    "roomName": room
                                                })

            if (!sprite) {
                    // Error Handling
                    console.log("Error creating object");
                }
        }

        function getX(day) {
            var ret
            if (day === "Mon") { ret = 0 + 1 }
            else if (day === "Tue") { ret = (tableRoot.width / 5) }
            else if (day === "Wed") { ret = (tableRoot.width / 5) * 2 }
            else if (day === "Thu") { ret = (tableRoot.width / 5) * 3 }
            else if (day === "Fri") { ret = (tableRoot.width / 5) * 4 }

            return ret
        }

        function getY(startH, startM) {
            var ret
            ret = ((startH - firstHour) + (startM / 60)) * tableRoot.height / 13


            return ret
        }

        function getHeight(startH, startM, endH, endM) {
            var ret
            var start = ((startH - firstHour) + (startM / 60)) * tableRoot.height / 13
            var end = ((endH - firstHour) + (endM / 60)) * tableRoot.height / 13
            ret = end - start

            return ret
        }

        Row {
            Repeater {
                model: 5

                Column {
                    Repeater {
                        model: 13
                        Rectangle {
                            width: tableRoot.width / 5
                            height: tableRoot.height / 13
                            color: "#FAFAFA"
                            border.color: "#000000"
                        }
                    }
                }
            }
        }

    }
}
