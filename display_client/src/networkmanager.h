#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QFile>
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
    Q_INVOKABLE void debugPostMethod();

private:
    QNetworkAccessManager *networkManager;
    QNetworkRequest request;

    JSONHandler *jsonHandler;

    // To close the image after sending it
    QFile *sentImage;

private slots:
    void managerDone(QNetworkReply *reply);
};

#endif // NETWORKMANAGER_H
