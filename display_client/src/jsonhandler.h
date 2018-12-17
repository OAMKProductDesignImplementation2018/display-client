#ifndef JSONHANDLER_H
#define JSONHANDLER_H

#include <QJsonArray>
#include <QJsonObject>
#include <QMap>
#include <QObject>

#include "dataupdate.h"

static const QVector<QString> weekDays {
    "Ma",
    "Ti",
    "Ke",
    "To",
    "Pe",
    "La",
    "Su"
};

class JSONHandler final : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(JSONHandler)

public:
    // Reads JSON from Azure, checks for errors and checks if person is recognized
    void checkPersonData(const QJsonObject data);
    // Parses organization data and token from JSON
    void parseOrganizationData(const QJsonObject data);
    // Parses person's data from JSON if person was recognized
    void parsePersonData(const QJsonObject data);
    // Parses schedule from JSON
    void parseScheduleData(const QJsonArray data);
    // Parses lunch menu from JSON
    void parseLunchMenuData(const QJsonObject data);
    // Parses news feed from RSS/XML
    void parseNewsFeed(const QByteArray data);

    QMap<QString, bool> foodFilterMap;

    static JSONHandler& getInstance();

signals:
    void jsonDataSent(QMap<QString, QString>);
    void scheduleUrlReceived(const QString);
    void lunchMenuUrlReceived(const QString);
    void personRecognized();
    void apiTokenDataReceived();
    void newLunchMenuDataReceived(); // to clear previous entries
    void newsDataReceived();
    void updateIdleStateData();

private:
    // JSON data members
    // From Azure api
    const QString tokenId = "token";
    const QString organizationName = "organization";

    const QString firstName = "firstname";
    const QString lastName = "lastname";

    const QString schedule = "schedule";

    const QString foodMenu = "foodMenu";
    const QString foodMenuName = "name";
    const QString foodMenuUrl = "url";
    const QString foodFilters = "filters";

    // From schedule API
    const QString scheduleRawName = "varaus";
    const QString scheduleRawStart = "alku"; // in unix time
    const QString scheduleRawEnd = "loppu"; // in unix time
    const QString scheduleRawTeacher = "opettaja";
    const QString scheduleRawRoom = "tila";
    const QString scheduleRawId = "toteutus";

    // From lunch menu API
    const QString lunchMenuRaw = "LunchMenu";
    const QString lunchSetMenusRaw = "SetMenus";
    const QString lunchNameRaw = "Name";
    const QString lunchMealsRaw = "Meals";
    const QString lunchDietsRaw = "Diets";

    const QString notes = "notes";
    const QString notesTitle = "title";
    const QString notesContent = "contents";
    const QString notesDay = "day";
    const QString notesStart = "start";
    const QString notesEnd = "end";

    JSONHandler() = default;
    ~JSONHandler() = default;
};

#endif // JSONHANDLER_H
