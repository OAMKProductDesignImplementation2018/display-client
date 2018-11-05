import QtQuick 2.0

Item {
    state: "Default"

    Loader {
        id: baseUILoader

        anchors.fill: parent
        sourceComponent: defaultView
    }

    states: [
        State {
            name: "Default"
            PropertyChanges {
                target: baseUILoader
                sourceComponent: defaultView
            }
        },
        State {
            name: "Personal"
            PropertyChanges {
                target: baseUILoader
                sourceComponent: personalView
            }
        }
    ]
}
