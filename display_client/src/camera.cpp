#include "camera.h"
#include <QCameraViewfinder>

Camera::Camera() {
}

Camera::~Camera() {
    // Remove all captured pictures when program is closed
    removeAllImages();
}

void Camera::removeAllImages() {
    const auto pathToPictures = QDir(getPathToSavedPictures());
    if (!pathToPictures.exists())
        return;

    // Find all captured pictures
    QStringList pictureList = pathToPictures.entryList(QStringList() << "*.jpg" << "*.JPG", QDir::Files);
    for (auto pictureName : pictureList) {
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
        if (itr > MAX_IMAGE_COUNT) {
            removeAllImages();
            itr = 1;
        }

        newImagePath = QFileInfo(getPathToSavedPictures() + "/image" + QString::number(itr) + ".jpg");
        ++itr;
    } while (newImagePath.exists());

    // Since QML saves the picture to default location (user/Pictures @ win10)
    // move the file inside application directory by renaming its path
    auto currentImagePath = QDir(path);
    if (!currentImagePath.rename(path, newImagePath.absoluteFilePath()))
        qDebug() << "Rename failed! Image is stored in the default location (" << path << ").";
}

QString Camera::getPathToSavedPictures() const {
    return QCoreApplication::applicationDirPath() + "/" + directoryName;
}
