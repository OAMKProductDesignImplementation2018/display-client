#include <QHttpPart>
#include <QHttpMultiPart>
#include <QJsonDocument>
#include <QJsonObject>

#include "camera.h"
#include "networkmanager.h"

NetworkManager::NetworkManager()
{
    apiAzure = new QNetworkAccessManager();

    jsonHandler = JSONHandler::getInstance();

    sentImage = nullptr;

    QObject::connect(apiAzure, &QNetworkAccessManager::finished,
        this, &NetworkManager::azureReply);

    qDebug() << "OpenSSL-version:";
    qDebug() << QSslSocket::sslLibraryVersionString();
    qDebug() << "- should be 1.0.2p";
}

NetworkManager::~NetworkManager() {
    delete apiAzure;
    delete jsonHandler;
    delete sentImage;
}

// Sends Einstein's image to face detection API
void NetworkManager::postEinsteinImage() {
    const auto pathToPictures = QDir(Camera::getPathToSavedPictures());
    if (!pathToPictures.exists()) {
        qDebug() << "Picture directory does not exist!";
        return;
    }

    sentImage = new QFile(pathToPictures.path() + "/einstein.jpg");
    if (!sentImage->exists()) {
        qDebug() << "Einstein's picture does not exist!";
        return;
    }

    // Send image in QHttpMultiPart
    const auto multipart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    // Append image to multipart as QHttpPart
    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/jpeg"));
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"image\""));
    sentImage->open(QIODevice::ReadOnly);
    imagePart.setBodyDevice(sentImage);
    sentImage->setParent(multipart);

    multipart->append(imagePart);

    request.setUrl(QUrl("https://appinterfaceface.azurewebsites.net/api/ScreenTrigger"));
    apiAzure->post(request, multipart);

    qDebug() << "Request sent";
}

void NetworkManager::postImage() {
    const auto pathToPictures = QDir(Camera::getPathToSavedPictures());
    if (!pathToPictures.exists()) {
        qDebug() << "Picture directory does not exist!";
        return;
    }

    // Find all captured pictures
    QStringList pictureList = pathToPictures.entryList(QStringList() << "*.jpg" << "*.JPG", QDir::Files);

    // Remove Einstein from pictureList array (Einstein is sent in different function)
    for (auto itr = 0; itr < pictureList.size(); ++itr) {
        if (pictureList.at(itr).contains("einstein.jpg")) {
            pictureList.removeAt(itr);
        }
    }

    // Check if there's any pictures
    if (pictureList.isEmpty()) {
        qDebug() << "Picture directory is empty!";
        return;
    }

    // Get the newest picture
    sentImage = new QFile(pathToPictures.path() + "/" + pictureList.at(pictureList.size() - 1));

    // Send image in QHttpMultiPart
    const auto multipart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    // Append image to multipart as QHttpPart
    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/jpeg"));
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"image\""));
    sentImage->open(QIODevice::ReadOnly);
    imagePart.setBodyDevice(sentImage);
    sentImage->setParent(multipart);

    multipart->append(imagePart);

    request.setUrl(QUrl("https://appinterfaceface.azurewebsites.net/api/ScreenTrigger"));
    apiAzure->post(request, multipart);

    qDebug() << "Request sent";
}

void NetworkManager::azureReply(QNetworkReply *reply) {
    // Close the file after finished signal
    if (sentImage != nullptr) {
        sentImage->close();
        delete sentImage;
    }

    // Check for network errors
    if (reply->error()) {
        qDebug() << "Error: " << reply->errorString();
        return;
    }

    // Set answer into QString
    QByteArray answer = reply->readAll();

    // Cast it to QJsonDocument
    const auto jsonDocument = QJsonDocument::fromJson(answer);
    if (jsonDocument.isNull()) {
        qDebug() << "Document is empty!";
        return;
    }

    if (!jsonDocument.isObject()) {
        qDebug() << "Document is not a JSON object!";
        return;
    }

    // Send it as QJsonObject
    jsonHandler->checkPersonData(jsonDocument.object());
}
