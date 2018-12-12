import QtQuick 2.0

Rectangle {
    z: 10
    color: "#FAFAFA"
    border.color: "#3465A4"

    property string courseName: ""
    property string teacherName: ""
    property string roomName: ""

    Text {
        id: courseName
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: teacherName.top
        font.pixelSize: 10
        font.bold: true
        elide: Text.ElideRight

        width: parent.width

        fontSizeMode: Text.Fit
        horizontalAlignment: Text.AlignHCenter

        text: parent.courseName
    }

    Text {
        id: teacherName
        anchors.centerIn: parent
        font.pixelSize: 10
        elide: Text.ElideRight

        fontSizeMode: Text.Fit
        horizontalAlignment: Text.AlignHCenter

        text: parent.teacherName
    }

    Text {
        id: room
        anchors.top: parent.teacherName.length > 0 ? teacherName.bottom : courseName.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 10
        elide: Text.ElideRight

        fontSizeMode: Text.Fit
        horizontalAlignment: Text.AlignHCenter

        text: parent.roomName
    }
}
