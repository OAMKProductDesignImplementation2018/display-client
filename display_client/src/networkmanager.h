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
    // Gets news RSS feed
    Q_INVOKABLE void getNewsFeed();

    // Debug methods
    // Sends Einstein's photo
    Q_INVOKABLE void postEinsteinImage();
    // Gets TVT18SPO schedule
    Q_INVOKABLE void debugGetSchedule() { getSchedule("https://oiva.oamk.fi/_lukkarikone/kalenteri/json/varaukset.php?ryhma=TVT18SPO"); }
    // Gets OAMK's lunch menu
    Q_INVOKABLE void debugGetLunchMenu() {
        const QString lunchUrl = "https://www.amica.fi/api/restaurant/menu/day?date=" + QDateTime::currentDateTime().toString("yyyy-MM-dd") + "&language=fi&restaurantPageId=66287";
        getLunchMenu(lunchUrl);
    }

private:
    volatile bool waitingForReply;

    // Network connector for Azure
    QNetworkAccessManager *apiAzure;
    // Network connector for schedule
    QNetworkAccessManager *apiSchedule;
    // Network connector for lunch menu
    QNetworkAccessManager *apiLunchMenu;
    // Network connector for news
    QNetworkAccessManager *apiNews;

    // To close the image after sending it
    QFile *sentImage;

    const QUrl apiAzureUrl = QUrl("https://appinterfaceface.azurewebsites.net/api/ScreenTrigger?code=K2r/oiVCg8r75br2zaP8SQ5rz83oVOwzk49epoBL22IYK51BamQSSQ==");

    // Azure api data fields
    const QByteArray organizationIdField = "organizationid";
    const QByteArray apiKeyField = "apikey";
    const QByteArray deviceIdField = "deviceid";


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
    // Reply from news
    void newsReply(QNetworkReply *reply);
};

#endif // NETWORKMANAGER_H
