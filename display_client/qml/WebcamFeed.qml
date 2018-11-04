import QtQuick 2.0
import QtMultimedia 5.9

Item {
    Camera {
        id: webcam

        imageCapture {
            onImageCaptured: {
                previewImage.source = preview
            }
        }
    }

    VideoOutput {
        id: videoOutput
        source: webcam
        focus: visible
        anchors.fill: parent

        MouseArea {
            anchors.fill: parent
            onClicked: webcam.imageCapture.capture();
        }
    }

    Image {
        id: previewImage

        width: videoOutput.width
        height: videoOutput.height
    }
}
