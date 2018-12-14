import QtQuick 2.0

Item {
    id: displayBase

    state: dataUpdate.displayState

    Component { id: displayDefault; DisplayDefault { } }
    Component { id: displayPersonal; DisplayPersonal { } }

    Connections {
        target: dataUpdate
        onDisplayStateChanged: {
            state = dataUpdate.displayState
        }
    }

    DebugButton {
        x: 0
        y: 0
        z: 2
        width: 40
        height: 24

        color: "#FF0000"

        onButtonPressed: {
            // Logout
            dataUpdate.stateExpired();
        }
    }

    Loader {
        id: displayLoader
        anchors.fill: parent
        sourceComponent: displayDefault
    }

    states: [
        State {
            name: "Default"
            PropertyChanges {
                target: displayLoader
                sourceComponent: displayDefault
            }
        },
        State {
            name: "Personal"
            PropertyChanges {
                target: displayLoader
                sourceComponent: displayPersonal
            }
        }
    ]
}
