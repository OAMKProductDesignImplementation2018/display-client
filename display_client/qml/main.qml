import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Window 2.2

import DataUpdate 0.1
import CaptureImage 0.1

Window {
    id: mainWindowRoot
    visible: true
    width: 900
    height: 1600
    flags: Qt.FramelessWindowHint
    visibility: Window.Windowed

    Component.onCompleted: {
        setX(Screen.width / 2 - width / 2)
        setY(Screen.height / 2 - height / 2)
    }

    Item {
        id: mainWindow
        anchors.fill: parent

        // Qt Classes
        DataUpdate { id: dataUpdate }
        CaptureImage { id: captureImage }

        // QML Components
        Component { id: defaultView; DisplayDefault { } }
        Component { id: personalView; DisplayPersonal { } }

        Item {
            id: background
            anchors.fill: parent

            Rectangle {
                anchors.fill: parent
                color: "#F0F0F0"
                border.color: "#000000"
                border.width: 1
            }
        }

        WebcamFeed {
            anchors.fill: parent
        }

        Item {
            id: debugButtons
            z: 1
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            width: parent.width
            height: 50

            DebugButton {
                id: quitButton
                anchors.left: parent.left
                anchors.top: parent.top

                radius: 2
                borderWidth: 1

                width: 50
                height: 50

                Text {
                    anchors.centerIn: parent
                    text: "X"
                    font.pixelSize: 32
                }

                onButtonPressed: {
                    Qt.quit()
                }
            }

            DebugButton {
                id: stateDefaultButton
                anchors.left: quitButton.right
                anchors.leftMargin: 24
                anchors.verticalCenter: parent.verticalCenter
                height: 50
                width: 160

                Text {
                    anchors.centerIn: parent
                    text: "State: Default"
                    font.pixelSize: 20
                }

                onButtonPressed: {
                    baseUI.pop(null)
                }
            }

            DebugButton {
                id: statePersonalButton
                anchors.left: stateDefaultButton.right
                anchors.leftMargin: 8
                anchors.verticalCenter: parent.verticalCenter
                height: 50
                width: 160

                Text {
                    anchors.centerIn: parent
                    text: "State: Personal"
                    font.pixelSize: 20
                }

                onButtonPressed: {
                    baseUI.push(baseUI.displayPersonal)
                }
            }

            DebugButton {
                id: showScheduleButton
                anchors.left: statePersonalButton.right
                anchors.leftMargin: 8
                anchors.verticalCenter: parent.verticalCenter
                height: 50
                width: 50

                Text {
                    anchors.centerIn: parent
                    text: "S"
                    font.pixelSize: 24
                }

                onButtonPressed: {
                    dataUpdate.scheduleVisible = !dataUpdate.scheduleVisible
                }
            }

            DebugButton {
                id: showFoodMenuButton
                anchors.left: showScheduleButton.right
                anchors.leftMargin: 8
                anchors.verticalCenter: parent.verticalCenter
                height: 50
                width: 50

                Text {
                    anchors.centerIn: parent
                    text: "F"
                    font.pixelSize: 24
                }

                onButtonPressed: {
                    dataUpdate.foodMenuVisible = !dataUpdate.foodMenuVisible
                }
            }

            DebugButton {
                id: showNotesButton
                anchors.left: showFoodMenuButton.right
                anchors.leftMargin: 8
                anchors.verticalCenter: parent.verticalCenter
                height: 50
                width: 50

                Text {
                    anchors.centerIn: parent
                    text: "N"
                    font.pixelSize: 24
                }

                onButtonPressed: {
                    dataUpdate.notesVisible = !dataUpdate.notesVisible
                }
            }

            DebugButton {
                id: showNewsButton
                anchors.left: showNotesButton.right
                anchors.leftMargin: 8
                anchors.verticalCenter: parent.verticalCenter
                height: 50
                width: 50

                Text {
                    anchors.centerIn: parent
                    text: "N"
                    font.pixelSize: 24
                }

                onButtonPressed: {
                    dataUpdate.newsVisible = !dataUpdate.newsVisible
                }
            }

            DebugButton {
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                width: 90
                height: 50
                color: "#00000000"
                borderColor: "#000000"

                Text {
                    anchors.centerIn: parent
                    text: "Signal test"
                    font.pixelSize: 16
                }

                onButtonPressed: {
                    dataUpdate.updateUI()
                }
            }
        }

        Item {
            id: displayBase
            anchors.fill: parent

            StackView {
                id: baseUI
                anchors.fill: parent
                initialItem: displayDefault

                Component { id: _displayDefault; DisplayDefault { } }
                Component { id: _displayPersonal; DisplayPersonal { } }

                property DisplayDefault displayDefault: _displayDefault.createObject()
                property DisplayPersonal displayPersonal: _displayPersonal.createObject()

                delegate: StackViewDelegate {
                    function transitionFinished(properties)
                    {
                        properties.exitItem.opacity = 1
                    }

                    pushTransition: StackViewTransition {
                        PropertyAnimation {
                            target: enterItem
                            property: "opacity"
                            from: 0
                            to: 1
                            duration: 500
                            easing.type: Easing.OutQuad
                        }

                        PropertyAnimation {
                            target: exitItem
                            property: "opacity"
                            from: 1
                            to: 0
                            duration: 500
                            easing.type: Easing.OutQuad
                        }
                    }
                }
            }
        }
    }
}
