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

    // Debug methods
    // Sends Einstein's photo
    Q_INVOKABLE void postEinsteinImage();
    // Gets TVT18SMO schedule
    Q_INVOKABLE void debugGetSchedule() { getSchedule("https://oiva.oamk.fi/_lukkarikone/kalenteri/json/varaukset.php?ryhma=TVT18SPO"); }

private:
    volatile bool waitingForReply;

    // Network connector for Azure
    QNetworkAccessManager *apiAzure;
    // Network connector for schedule
    QNetworkAccessManager *apiSchedule;
    // Network connector for lunch menu
    QNetworkAccessManager *apiLunchMenu;

    // To close the image after sending it
    QFile *sentImage;

    const QUrl apiAzureUrl = QUrl("https://appinterfaceface.azurewebsites.net/api/ScreenTrigger?code=K2r/oiVCg8r75br2zaP8SQ5rz83oVOwzk49epoBL22IYK51BamQSSQ==");

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
