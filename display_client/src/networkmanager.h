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
    QNetworkRequest request;

    // Network connector for Azure
    QNetworkAccessManager *apiAzure;
    // Network connector for schedule
    QNetworkAccessManager *apiSchedule;
    // Network connector for lunch menu
    QNetworkAccessManager *apiLunchMenu;

    // To close the image after sending it
    QFile *sentImage;

    const QUrl apiAzureUrl = QUrl("https://appinterfaceface.azurewebsites.net/api/ScreenTrigger");

private slots:
    // Gets schedule
    void getSchedule(const QString scheduleUrl);
    // Gets lunch menu
    void getLunchMenu(const QString lunchMenuUrl);

    // Reply from Azure
    void azureReply(QNetworkReply *reply);
    // Reply from schedule api
    void scheduleReply(QNetworkReply *reply);
    // Reply from lunch menu api
    void lunchMenuReply(QNetworkReply *reply);
};

#endif // NETWORKMANAGER_H
