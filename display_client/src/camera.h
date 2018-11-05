#ifndef CAMERA_H
#define CAMERA_H

#include <QCamera>
#include <QDir>
#include <QImageReader>
#include <QWidget>

const QString directoryName = "CameraImages";
const uint8_t MAX_IMAGE_COUNT = 10;

class Camera : public QObject {
    Q_OBJECT

public:
    Camera();
    ~Camera();

    QString getPathToSavedPictures() const;
    void removeAllImages();

public slots:
    void moveImage(const QString path);
};

#endif // CAMERA_H
