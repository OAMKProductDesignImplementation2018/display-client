import QtQuick 2.0
import QtMultimedia 5.9

Item {
    Connections {
        target: captureImage
    }

    Camera {
        id: webcam

        imageCapture {
            onImageSaved: {
                captureImage.moveImage(path)
            }
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: webcam.imageCapture.capture();
    }
}
