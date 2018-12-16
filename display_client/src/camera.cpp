#include <QCameraViewfinder>

#include "camera.h"

volatile bool Camera::running = true;

Camera::Camera() {
    // Initialize and start capture timer
    cameraTimer = new QTimer(this);
    QObject::connect(cameraTimer, &QTimer::timeout,
                     this, &Camera::capture);
    cameraTimer->start(cameraDelay);
}

Camera::~Camera() {
    // Remove all captured pictures when program is closed
    removeAllImages();

    delete cameraTimer;
}

QString Camera::getPathToSavedPictures() {
    return QCoreApplication::applicationDirPath() + "/" + directoryName;
}

void Camera::enableCapturing(const bool enable) {
    running = enable;
}

void Camera::removeAllImages() {
    const auto pathToPictures = QDir(getPathToSavedPictures());
    if (!pathToPictures.exists())
        return;

    // Find all captured pictures
    const QStringList pictureList = pathToPictures.entryList(QStringList() << "*.jpg" << "*.JPG", QDir::Files);
    for (const auto &pictureName : pictureList) {
        // Skip Einstein's picture
        if (pictureName.contains("einstein", Qt::CaseInsensitive))
            continue;

        // Get file and remove it
        QFile image(pathToPictures.path() + "/" + pictureName);
        if (image.isOpen())
            image.close();
        image.remove();
    }
}

void Camera::moveImage(const QString path) {
    // Create directory for pictures if it does not exist
    const auto pathToPictures = QDir(getPathToSavedPictures());
    if (!pathToPictures.exists())
        pathToPictures.mkpath(".");

    // Create new file name for picture
    auto newImagePath = QFileInfo();
    int itr = 1;
    do {
        // Don't fill harddrive with pictures
        if (itr > MAX_IMAGE_COUNT) {
            removeAllImages();
            itr = 1;
        }

        newImagePath = QFileInfo(getPathToSavedPictures() + "/image" + QString::number(itr) + ".jpg");
        ++itr;
    } while (newImagePath.exists());

    // Since QML saves the pictures to default location (user/Pictures @ win10),
    // move the picture inside application directory by renaming its path
    auto currentImagePath = QDir(path);
    if (!currentImagePath.rename(path, newImagePath.absoluteFilePath()))
        qDebug() << "Rename failed! Image is stored in the default location (" << path << ").";
}

void Camera::capture() {
    if (!running)
        return;

    // Emit capture signal to QML
    emit captureImage();
}
