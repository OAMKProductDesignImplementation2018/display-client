import QtQuick 2.0

Item {
    id: root

    property var days: ["Ma", "Ti", "Ke", "To", "Pe"]
    property int firstHour: 8 // i.e. schedule starts at 8; Maybe link to Q_PROPERTY ?
    property string borderColor: "#B2B2B2"


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

    Rectangle {
        width: parent.width
        height: parent.height

        border.color: borderColor

        Row {
            id: daysRoot
            anchors.left: timesRoot.right
            anchors.right: parent.right

            Repeater {
                id: dayRectangles
                model: days
                Rectangle {
                    width: daysRoot.width / 5
                    height: root.height / 18
                    color: "#3465A4"

                    Text {
                        font.pixelSize: 21
                        font.capitalization: Font.AllUppercase
                        text: modelData
                        color: "white"

                        // Dynamic font size
                        fontSizeMode: Text.Fit
                        width: parent.width
                        height: parent.height

                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter

                        anchors.centerIn: parent
                    }

                    // Left border (only show for first item)
                    Rectangle {
                        width: 1
                        height: parent.height
                        color: borderColor

                        anchors.left: parent.left
                        visible: index == 0 ? true : false
                    }

                    // Right border
                    Rectangle {
                        width: 1
                        height: parent.height
                        color: borderColor

                        anchors.right: parent.right
                    }

                    // Bottom border
                    Rectangle {
                        width: parent.width
                        height: 1
                        color: borderColor

                        anchors.bottom: parent.bottom
                    }

                    // Top border
                    Rectangle {
                        width: parent.width
                        height: 1
                        color: borderColor

                        anchors.top: parent.top
                    }
                }
            }
        }

        Column {
            id: timesRoot
            x: 1
            anchors.top: daysRoot.bottom
            anchors.bottom: parent.bottom
            width: root.width / 9

            Repeater {
                model: 13 // times

                Rectangle {
                    color: "#3465A4"
                    width: root.width / 9
                    height: timesRoot.height / 13

                    Text {
                        font.pixelSize: 21
                        text: (index + firstHour) + "-" + (index + firstHour + 1) // modelData
                        color: "white"

                        // Dynamic font size
                        fontSizeMode: Text.Fit
                        width: parent.width
                        height: parent.height

                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }

                    // Right border
                    Rectangle {
                        width: 1
                        height: parent.height
                        color: borderColor

                        anchors.right: parent.right
                    }

                    // Top border (only show for first item)
                    Rectangle {
                        width: parent.width
                        height: 1
                        color: borderColor

                        anchors.top: parent.top
                        visible: index == 0 ? true : false
                    }

                    // Bottom border
                    Rectangle {
                        width: parent.width
                        height: 1
                        color: borderColor

                        anchors.bottom: parent.bottom
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
                if (day === days[0]) { ret = 0 }
                else if (day === days[1]) { ret = (tableRoot.width / 5) }
                else if (day === days[2]) { ret = (tableRoot.width / 5) * 2 }
                else if (day === days[3]) { ret = (tableRoot.width / 5) * 3 }
                else if (day === days[4]) { ret = (tableRoot.width / 5) * 4 }

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
                                color: "white"

                                // Right border
                                Rectangle {
                                    width: 1
                                    height: parent.height
                                    color: borderColor

                                    anchors.right: parent.right
                                }

                                // Bottom border
                                Rectangle {
                                    width: parent.width
                                    height: 1
                                    color: borderColor

                                    anchors.bottom: parent.bottom
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
