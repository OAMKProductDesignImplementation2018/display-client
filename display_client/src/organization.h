#ifndef ORGANIZATION_H
#define ORGANIZATION_H

#include <QDebug>

class Organization final : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Organization)

public:
    static Organization& getInstance();

    QString id = "1";
    QString deviceName = "nayttolaite";
    QString apiKey = "null";

    QString lunchUrl = "null";
    const QString newsUrl = "https://news.yahoo.com/rss/europe";

    // News container
    QVector<QStringList> newsContainer;

    // Methods
    void setRestaurantName(const QString name);
    void setOrganizationName(const QString name);

signals:
    void restaurantNameUpdated(QString);
    void organizationNameUpdated(QString);

private:
    Organization() = default;
    ~Organization() = default;

    QString _restaurantName = "null";
    QString _organizationName = "null";
};

#endif // ORGANIZATION_H
