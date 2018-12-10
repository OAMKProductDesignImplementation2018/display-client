import QtQuick 2.0

Item {
    Rectangle {
        id: debugBox
        anchors.fill: parent

        border.color: "#000000"
        color: "#FFFFFF"
    }

    Connections {
        target: dataUpdate

        onFoodMenuClear: {
            menuListModel.clear()
        }

        onFoodMenuAdd: {
            menuListModel.append( { "type": type, "name": name })
        }
    }

    ListModel {
        id: menuListModel
    }

    ListView {
        id: menuListView
        anchors.fill: parent
        orientation: ListView.Vertical
        model: menuListModel
        interactive: false

        delegate: Rectangle {
            width: parent.width
            height: menuListView.height / menuListModel.count
            color: index % 2 ? "#FFDCA2" : "#FFEFD5"
            border.color: "#4d3000"

            Text {
                id: foodType
                x: 6
                y: 4
                text: type
                font.pixelSize: 14
            }

            Text {
                id: foodContents
                x: 4
                anchors.top: foodType.bottom
                anchors.topMargin: 4
                width: parent.width - 4
                clip: true
                maximumLineCount: {
                    if (menuListModel.count > 6) { 1 }
                    else if (menuListModel.count > 4) { 2 }
                    else { 3 }
                }
                elide: Text.ElideRight
                wrapMode: Text.WordWrap
                font.pixelSize: {
                    if (menuListModel.count > 6) { 18 }
                    else if (menuListModel.count > 4) { 21 }
                    else { 24 }
                }

                text: name
            }
        }

        Rectangle {
            id: menuListViewBG
            z: -1
            anchors.fill: parent
            color: "#FFDCA2"
        }
    }
}
