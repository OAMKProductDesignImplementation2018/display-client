#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

#include "jsonhandler.h"

class NetworkManager : public QObject
{
    Q_OBJECT

public:
    NetworkManager();
    ~NetworkManager();

    Q_INVOKABLE void debugFunction();

private:
    QNetworkAccessManager *networkManager;
    QNetworkRequest request;

    JSONHandler *jsonHandler;

private slots:
    void managerDone(QNetworkReply *reply);
};

#endif // NETWORKMANAGER_H
