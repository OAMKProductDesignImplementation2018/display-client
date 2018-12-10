import QtQuick 2.0

Item {
    id: root

    property var days: ["Mon", "Tue", "Wed", "Thu", "Fri"]
    property int firstHour: 8 // i.e. schedule starts at 8; Maybe link to Q_PROPERTY ?


    Connections {
        target: dataUpdate

         onNewScheduleEvent: {
             var day = ""
             var name = ""
             var teacher = ""
             var room = ""
             var startH = ""
             var startM = ""
             var endH = ""
             var endM = ""

             // Received QVariantMap vMap
             for (var item in vMap) {
                 if (item === "day")
                     day = vMap[item]
                 else if (item === "name")
                     name = vMap[item]
                 else if (item === "teacher")
                     teacher = vMap[item]
                 else if (item === "room")
                     room = vMap[item]
                 else if (item === "startH")
                     startH = vMap[item]
                 else if (item === "startM")
                     startM = vMap[item]
                 else if (item === "endH")
                     endH = vMap[item]
                 else if (item === "endM")
                     endM = vMap[item]
             }

             tableRoot.createEvent(day, startH, startM, endH, endM, name, teacher, room)
         }
    }

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
            model: 13 // times

            Rectangle {
                color: "#00CCFF"
                border.color: "#5A5A5A"
                width: root.width / 9
                height: timesRoot.height / 13

                Text {
                    anchors.centerIn: parent
                    color: "#000000"
                    text: (index + firstHour) + "-" + (index + firstHour + 1) // modelData
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

            if (sprite === null) {
                    // Error Handling
                    console.log("Error creating object");
                }
        }

        function getX(day) {
            var ret
            if (day === "Mon") { ret = 0 }
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
