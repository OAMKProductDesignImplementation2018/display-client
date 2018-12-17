#include <QHttpPart>
#include <QHttpMultiPart>
#include <QJsonDocument>
#include <QJsonObject>

#include "camera.h"
#include "networkmanager.h"

NetworkManager::NetworkManager() {
    apiAzure = new QNetworkAccessManager();
    apiSchedule = new QNetworkAccessManager();
    apiLunchMenu = new QNetworkAccessManager();
    apiNews = new QNetworkAccessManager();

    sentImage = nullptr;
    waitingForReply = false;
    setWaitingForApiToken(true);

    QObject::connect(apiAzure, &QNetworkAccessManager::finished,
        this, &NetworkManager::azureReply);
    QObject::connect(apiSchedule, &QNetworkAccessManager::finished,
        this, &NetworkManager::scheduleReply);
    QObject::connect(apiLunchMenu, &QNetworkAccessManager::finished,
        this, &NetworkManager::lunchMenuReply);
    QObject::connect(apiNews, &QNetworkAccessManager::finished,
        this, &NetworkManager::newsReply);

    QObject::connect(&JSONHandler::getInstance(), &JSONHandler::scheduleUrlReceived,
        this, &NetworkManager::getSchedule);
    QObject::connect(&JSONHandler::getInstance(), &JSONHandler::lunchMenuUrlReceived,
        this, &NetworkManager::getLunchMenu);
    QObject::connect(&JSONHandler::getInstance(), &JSONHandler::personRecognized,
        this, &NetworkManager::getNewsFeed);
    QObject::connect(&JSONHandler::getInstance(), &JSONHandler::updateIdleStateData,
        this, &NetworkManager::updateIdleState);

    qDebug() << "OpenSSL-version:";
    qDebug() << QSslSocket::sslLibraryVersionString();
    qDebug() << "- should be 1.0.2p";

    // On create, send API request to Azure to get API token and organization data
    postImage();
}

NetworkManager::~NetworkManager() {
    delete apiAzure;
    delete apiSchedule;
    delete apiLunchMenu;
    delete apiNews;
    delete sentImage;
}

void NetworkManager::postImage() {
    // Wait for current request to finish before creating a new request
    if (waitingForReply) {
        qDebug() << "Canceling request";
        return;
    }

    // Send image in QHttpMultiPart
    const auto multipart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    // Append image to multipart as QHttpPart
    if (sentImage != nullptr) {
        QHttpPart imagePart;
        imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/jpeg"));
        imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"image\""));
        sentImage->open(QIODevice::ReadOnly);
        imagePart.setBodyDevice(sentImage);
        sentImage->setParent(multipart);

        multipart->append(imagePart);
    }

    // Add apikey and device id into network request
    QNetworkRequest networkRequest;
    networkRequest.setRawHeader(organizationIdField, Organization::getInstance().id.toUtf8());
    networkRequest.setRawHeader(apiKeyField, Organization::getInstance().apiKey.toUtf8());
    networkRequest.setRawHeader(deviceIdField, Organization::getInstance().deviceName.toUtf8());
    networkRequest.setUrl(apiAzureUrl);

    apiAzure->post(networkRequest, multipart);
    waitingForReply = true;
    qDebug() << "Request sent";
}

void NetworkManager::getImage() {
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

    postImage();
}

void NetworkManager::getNewsFeed() {
    apiNews->get(QNetworkRequest(QUrl(Organization::getInstance().newsUrl)));
}

void NetworkManager::updateIdleState() {
    getNewsFeed();
    getLunchMenu(Organization::getInstance().lunchUrl);
}

bool NetworkManager::waitingForApiToken() const {
    return _waitingForApiToken;
}

void NetworkManager::setWaitingForApiToken(const bool waiting) {
    _waitingForApiToken = waiting;
    emit waitingUpdated();
}

// Only for debugging
void NetworkManager::getEinsteinImage() {
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

    postImage();
}

void NetworkManager::getSchedule(const QString scheduleUrl) {
    apiSchedule->get(QNetworkRequest(QUrl(scheduleUrl)));
}

void NetworkManager::getLunchMenu(const QString lunchMenuUrl) {
    apiLunchMenu->get(QNetworkRequest(QUrl(lunchMenuUrl)));
}

void NetworkManager::azureReply(QNetworkReply *reply) {
    // Close the file after finished signal
    if (sentImage != nullptr) {
        sentImage->close();
        delete sentImage;
    }

    // Allow creating new requests when current request has replied
    waitingForReply = false;
    setWaitingForApiToken(false);

    // Check for network errors
    if (reply->error()) {
        qDebug() << "Error: " << reply->errorString();
        return;
    }

    // Set answer into QString
    const QByteArray answer = reply->readAll();

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
    JSONHandler::getInstance().checkPersonData(jsonDocument.object());
}

void NetworkManager::scheduleReply(QNetworkReply *reply) {
    // Check for network errors
    if (reply->error()) {
        qDebug() << "Error: " << reply->errorString();
        return;
    }

    // Read reply
    const QByteArray answer = reply->readAll();

    // Cast it to QJsonDocument
    const auto jsonDocument = QJsonDocument::fromJson(answer);
    if (jsonDocument.isNull()) {
        qDebug() << "Document is empty!";
        return;
    }

    if (!jsonDocument.isArray()) {
        qDebug() << "Document is not a JSON array!";
        return;
    }

    // Send it as QJsonArray
    JSONHandler::getInstance().parseScheduleData(jsonDocument.array());
}

void NetworkManager::lunchMenuReply(QNetworkReply *reply) {
    // Check for network errors
    if (reply->error()) {
        qDebug() << "Error: " << reply->errorString();
        return;
    }

    // Read reply
    const QByteArray answer = reply->readAll();

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
    JSONHandler::getInstance().parseLunchMenuData(jsonDocument.object());
}

void NetworkManager::newsReply(QNetworkReply *reply) {
    // Check for network errors
    if (reply->error()) {
        qDebug() << "Error: " << reply->errorString();
        return;
    }

    // Read reply
    const QByteArray answer = reply->readAll();

    JSONHandler::getInstance().parseNewsFeed(answer);
}
