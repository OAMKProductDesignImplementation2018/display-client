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

    // Sends latest image captured by camera
    Q_INVOKABLE void postImage();
    // Sends Einstein's photo
    Q_INVOKABLE void postEinsteinImage();

private:
    JSONHandler *jsonHandler;
    QNetworkRequest request;

    // Network connector for Azure
    QNetworkAccessManager *apiAzure;

    // To close the image after sending it
    QFile *sentImage;

private slots:
    // Reply from Azure
    void azureReply(QNetworkReply *reply);
};

#endif // NETWORKMANAGER_H
