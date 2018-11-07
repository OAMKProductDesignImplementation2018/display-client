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
