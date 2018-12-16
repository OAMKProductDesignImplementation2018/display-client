import QtQuick 2.0

Item {
    width: parent.width - 100
    height: 40

    x: 50
    y: 50

    Rectangle {
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        border.color: "#E1E8F1"
        color: "transparent"

        width: parent.width * 0.3
        height: parent.height



        Text {
            font.pixelSize: 21
            text: (dataUpdate.displayState === "Default") ?
                   dataUpdate.organizationName : dataUpdate.firstName + " " + dataUpdate.lastName
            color: "black"

            // Dynamic font size
            fontSizeMode: Text.Fit
            width: parent.width
            height: parent.height

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            anchors.centerIn: parent
        }

        MouseArea {
            anchors.fill: parent

            property int counter: 0;
            onReleased: {
                ++counter
                if (counter >= 3) {
                    dataUpdate.toggleDeveloperMode()
                    counter = 0
                }
            }
        }
    }

    Rectangle {
        y: 0
        anchors.centerIn: parent
        border.color: "#E1E8F1"
        color: "transparent"

        width: parent.width * 0.3
        height: parent.height

        Text {
            font.pixelSize: 28
            font.bold: true
            text: dataUpdate.timeString
            color: "black"

            // Dynamic font size
            fontSizeMode: Text.Fit
            width: parent.width
            height: parent.height

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            anchors.centerIn: parent
        }

        MouseArea {
            anchors.fill: parent

            onReleased: {
                dataUpdate.debugAddScheduleItem()
            }
        }
    }

    Rectangle {
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        border.color: "#E1E8F1"
        color: "transparent"

        width: parent.width * 0.3
        height: parent.height

        Text {
            font.pixelSize: 21
            text: dataUpdate.dateString
            color: "black"

            // Dynamic font size
            fontSizeMode: Text.Fit
            width: parent.width
            height: parent.height

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            anchors.centerIn: parent
        }

        MouseArea {
            anchors.fill: parent

            onReleased: {
                networkManager.debugGetSchedule()
                networkManager.debugGetLunchMenu()
                networkManager.debugGetNews()
            }
        }
    }
}
