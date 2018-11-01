import QtQuick 2.0

Item {
    Connections {
        target: testClass
        onTestSignalEmitted: {
            console.log("QML received signal")
        }
    }

    DebugButton {
        width: 50
        height: 50
        color: "#FF6600"
        borderColor: "#000000"
        opacity: 0.1

        anchors.right: parent.right
        anchors.top: parent.top

        onButtonPressed: {
            testClass.testFunction()
        }
    }
}
