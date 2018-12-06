#ifndef CAMERA_H
#define CAMERA_H

#include <QCamera>
#include <QDir>
#include <QImageReader>
#include <QTimer>
#include <QWidget>

const QString directoryName = "CameraImages";
const uint8_t MAX_IMAGE_COUNT = 10;

class Camera : public QObject {
    Q_OBJECT

public:
    Camera();
    ~Camera();

    static QString getPathToSavedPictures();
    void removeAllImages();

private:
    QTimer *cameraTimer;
    const int cameraDelay = 5000; // 5 secs

signals:
    void captureImage();

public slots:
    void moveImage(const QString path);
    void capture();
};

#endif // CAMERA_H
