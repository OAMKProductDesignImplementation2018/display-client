import QtQuick 2.0
import QtMultimedia 5.9

Item {
    Connections {
        target: captureImage

        onCaptureImage: {
            webcam.imageCapture.capture()
        }
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
}
