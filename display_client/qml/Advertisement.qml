import QtQuick 2.0

Item {
    id: root
    clip: true
    state: rootStates[currentState]

    property int currentState: 0
    property var rootStates: ["First", "Second", "Third", "Fourth"]


    Rectangle {
        anchors.fill: parent

        border.color: "#000000"
        color: "#FFFFFF"

//        Text {
//            anchors.centerIn: parent
//            font.pixelSize: 24
//            text: "Advertisement Item"
//            horizontalAlignment: Text.AlignHCenter
//        }
    }

    Item {
        id: adItem1
        width: parent.width
        height: parent.height
        visible: false

        Rectangle {
            anchors.fill: parent
            color: "#FF6600"

            Text {
                anchors.centerIn: parent
                text: "Advertisement 1"
            }
        }
    }

    Item {
        id: adItem2
        width: parent.width
        height: parent.height
        visible: false

        Rectangle {
            anchors.fill: parent
            color: "#0066FF"

            Text {
                anchors.centerIn: parent
                text: "Advertisement 2"
            }
        }
    }

    Item {
        id: adItem3
        width: parent.width
        height: parent.height
        visible: false

        Rectangle {
            anchors.fill: parent
            color: "#00FF66"

            Text {
                anchors.centerIn: parent
                text: "Advertisement 3"
            }
        }
    }

    Item {
        id: adItem4
        width: parent.width
        height: parent.height
        visible: false

        Rectangle {
            anchors.fill: parent
            color: "#FF0066"

            Text {
                anchors.centerIn: parent
                text: "Advertisement 4"
            }
        }
    }

    states: [
        State {
            name: "First"
            PropertyChanges {
                target: adItem1
                visible: true
            }
        },
        State {
            name: "Second"
            PropertyChanges {
                target: adItem2
                visible: true
            }
        },
        State {
            name: "Third"
            PropertyChanges {
                target: adItem3
                visible: true
            }
        },
        State {
            name: "Fourth"
            PropertyChanges {
                target: adItem4
                visible: true
            }
        }
    ]


    Timer {
        id: timer
        interval: 3000
        running: true
        repeat: true
        onTriggered: {
            if (currentState < 3)
                currentState++
            else
                currentState = 0
        }
    }
}
