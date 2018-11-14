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
}

void NetworkManager::debugFunction() {
    request.setUrl(QUrl("http://jsonplaceholder.typicode.com/todos/1"));
    networkManager->get(request);
}

void NetworkManager::managerDone(QNetworkReply *reply) {
    if (reply->error()) {
        qDebug() << reply->errorString();
        return;
    }

    QString answer = reply->readAll();

    qDebug() << answer;
}
