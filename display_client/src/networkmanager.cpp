#include "networkmanager.h"

#include <QJsonDocument>
#include <QJsonObject>

#include <QCoreApplication>
#include <QFile>

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

void NetworkManager::managerDone(QNetworkReply *reply) {
    if (reply->error()) {
        qDebug() << reply->errorString();
        return;
    }

    // Set answer into QString
    QString answer = reply->readAll();



    // For debugging
    QString path = QCoreApplication::applicationDirPath() + "/CameraImages/samplejson.txt";
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
        qDebug() << "fail";
    else
        answer = file.readAll();

    file.close();




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
