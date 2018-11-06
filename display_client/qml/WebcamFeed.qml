import QtQuick 2.0
import QtMultimedia 5.9

Item {
    Connections {
        target: captureImage
    }

    Camera {
        id: webcam

        deviceId: (QtMultimedia.defaultCamera.deviceId !== "") ? QtMultimedia.defaultCamera.deviceId : QtMultimedia.availableCameras[0].deviceId;
        captureMode: Camera.CaptureStillImage
        position: Camera.FrontFace

        imageCapture {
            onImageSaved: {
                captureImage.moveImage(path)
            }
        }
    }

    Timer {
        // For the sake of debugging, interval is set to 5 seconds, change this to proper interval later
        interval: 5000
        running: true
        repeat: true
        onTriggered: webcam.imageCapture.capture()
    }
}
