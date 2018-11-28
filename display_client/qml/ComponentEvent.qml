import QtQuick 2.0

Rectangle {
    z: 10
    color: "#B0B0B0"
    border.color: "#303030"

    property string courseName: ""
    property string teacherName: ""
    property string roomName: ""

    Text {
        id: courseName
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: teacherName.top
        font.pixelSize: 10

        text: parent.courseName
    }

    Text {
        id: teacherName
        anchors.centerIn: parent
        font.pixelSize: 10

        text: parent.teacherName
    }

    Text {
        id: room
        anchors.top: teacherName.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 10

        text: parent.roomName
    }
}
