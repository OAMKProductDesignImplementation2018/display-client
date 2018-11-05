import QtQuick 2.0
import QtMultimedia 5.9

Item {
    Connections {
        target: captureImage
    }

    Camera {
        id: webcam

        imageCapture {
            onImageCaptured: {
                previewImage.source = preview
            }
            onImageSaved: {
                captureImage.moveImage(path)
            }
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: webcam.imageCapture.capture();
    }

    /*VideoOutput {
        id: videoOutput
        source: webcam
        focus: visible
        anchors.fill: parent

        MouseArea {
            anchors.fill: parent
            onClicked: captureImage.
            //onClicked: webcam.imageCapture.capture();
        }
    }*/

    Image {
        id: previewImage
    }
}
