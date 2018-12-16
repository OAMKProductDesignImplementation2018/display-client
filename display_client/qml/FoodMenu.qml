import QtQuick 2.11

Item {
    property string borderColor: "#3465A4"

    Rectangle {
        anchors.fill: parent

        border.color: borderColor
        color: "white"
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

    Rectangle {
        id: restaurantNameRect
        width: parent.width
        height: parent.height / 13
        color: borderColor

        anchors.top: parent.top
        anchors.left: parent.left

        Text {
            font.pixelSize: 28
            text: "Amica Kotkantie"
            color: "white"

            // Dynamic font size
            fontSizeMode: Text.Fit
            width: parent.width
            height: parent.height

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }

    ListModel {
        id: menuListModel
    }

    ListView {
        id: menuListView
        anchors.top: restaurantNameRect.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        orientation: ListView.Vertical
        model: menuListModel
        interactive: false

        delegate: Rectangle {
            width: parent.width
            height: menuListView.height / menuListModel.count
            color: "white"

            property int paddingSize: 15

            Rectangle {
                id: foodType
                width: foodTypeText.paintedWidth + (paddingSize * 2)
                height: foodTypeText.paintedHeight * 1.5

                color: "#729FCF"

                anchors.top: parent.top
                anchors.left: parent.left

                Text {
                    id: foodTypeText
                    text: type
                    font.pixelSize: 12

                    leftPadding: paddingSize
                    rightPadding: paddingSize

                    // Dynamic font size
                    fontSizeMode: Text.Fit
                    width: parent.width
                    height: parent.height

                    verticalAlignment: Text.AlignVCenter
                }

                // Bottom border
                Rectangle {
                    width: parent.width
                    height: 1
                    color: borderColor

                    anchors.bottom: parent.bottom
                }

                // Right border
                Rectangle {
                    width: 1
                    height: parent.height
                    color: borderColor

                    anchors.right: parent.right
                }
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

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            // Left border
            Rectangle {
                width: 1
                height: parent.height
                color: borderColor

                anchors.left: parent.left
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
        }
    }
}
