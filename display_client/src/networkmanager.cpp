#include <QHttpPart>
#include <QHttpMultiPart>
#include <QJsonDocument>
#include <QJsonObject>

#include "camera.h"
#include "networkmanager.h"

NetworkManager::NetworkManager()
{
    networkManager = new QNetworkAccessManager();
    jsonHandler = new JSONHandler();

    QObject::connect(networkManager, SIGNAL(finished(QNetworkReply*)),
        this, SLOT(managerDone(QNetworkReply*)));
}

NetworkManager::~NetworkManager() {
    delete networkManager;
    delete jsonHandler;
}

void NetworkManager::debugFunction() {
    request.setUrl(QUrl("https://jsonplaceholder.typicode.com/todos/1"));
    networkManager->get(request);
}

void NetworkManager::debugPostMethod() {
    const auto pathToPictures = QDir(Camera::getPathToSavedPictures());
    if (!pathToPictures.exists()) {
        qDebug() << "Picture directory does not exist!";
        return;
    }

    // Find all captured pictures
    const QStringList pictureList = pathToPictures.entryList(QStringList() << "*.jpg" << "*.JPG", QDir::Files);
    if (pictureList.isEmpty()) {
        qDebug() << "Picture directory is empty!";
        return;
    }

    // Get the newest picture
    const auto image = new QFile(pathToPictures.path() + "/" + pictureList.at(pictureList.size() - 1));

    // Send image in QHttpMultiPart
    const auto multipart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    // Append image to multipart as QHttpPart
    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/jpeg"));
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"image\""));
    image->open(QIODevice::ReadOnly);
    imagePart.setBodyDevice(image);
    image->setParent(multipart);

    multipart->append(imagePart);

    request.setUrl(QUrl("https://appinterfaceface.azurewebsites.net/api/ScreenTrigger"));
    networkManager->post(request, multipart);
}

void NetworkManager::managerDone(QNetworkReply *reply) {
    if (reply->error()) {
        qDebug() << "Error: " << reply->errorString();
        return;
    }

    // Set answer into QString
    QString answer = reply->readAll();

    // Cast it to QJsonDocument
    const auto jsonDocument = QJsonDocument::fromJson(answer.toUtf8());
    if (jsonDocument.isNull()) {
        qDebug() << "Document is empty!";
        return;
    }

    if (!jsonDocument.isObject()) {
        qDebug() << "Document is not a JSON object!";
        return;
    }

    // Send it as QJsonObject
    jsonHandler->parseJSON(jsonDocument.object());
}
