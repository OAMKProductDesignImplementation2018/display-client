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
    Q_INVOKABLE void getImage();

    Q_PROPERTY (bool waitingForApiToken
                READ waitingForApiToken
                WRITE setWaitingForApiToken
                NOTIFY waitingUpdated)
    bool waitingForApiToken() const;
    void setWaitingForApiToken(const bool waiting);

    // Debug methods
    // Sends Einstein's photo
    Q_INVOKABLE void getEinsteinImage();
    // Gets TVT18SPO schedule
    Q_INVOKABLE void debugGetSchedule() { getSchedule("https://oiva.oamk.fi/_lukkarikone/kalenteri/json/varaukset.php?ryhma=TVT18SPO"); }
    // Gets OAMK's lunch menu
    Q_INVOKABLE void debugGetLunchMenu() {
        //const QString lunchUrl = "https://www.amica.fi/api/restaurant/menu/day?date=" + QDateTime::currentDateTime().toString("yyyy-MM-dd") + "&language=fi&restaurantPageId=66287";
        const QString lunchUrl = "https://www.amica.fi/api/restaurant/menu/day?date=2018-12-20&language=fi&restaurantPageId=66287";
        getLunchMenu(lunchUrl);
    }
    // Gets Yahoo news
    Q_INVOKABLE void debugGetNews() { getNewsFeed(); }

private:
    volatile bool waitingForReply;
    bool _waitingForApiToken;

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

signals:
    void waitingUpdated();

private slots:
    // Posts selected picture
    void postImage();
    // Gets schedule
    void getSchedule(const QString scheduleUrl);
    // Gets lunch menu
    void getLunchMenu(const QString lunchMenuUrl);
    // Gets news RSS feed
    void getNewsFeed();
    // Gets news and lunch menu to idle screen
    void updateIdleState();

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
