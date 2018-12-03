#ifndef JSONHANDLER_H
#define JSONHANDLER_H

#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QMap>
#include <QObject>

#include "dataupdate.h"

static const QVector<QString> weekDays {
    "Mon",
    "Tue",
    "Wed",
    "Thu",
    "Fri",
    "Sat",
    "Sun"
};

class JSONHandler final : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(JSONHandler)

public:
    // Reads JSON from Azure, checks for errors and checks if person is recognized
    void checkPersonData(const QJsonObject data);
    // Parses person's data from JSON if person was recognized
    void parsePersonData(const QJsonObject data);
    // Parses schedule from JSON
    void parseScheduleData(const QJsonArray data);
    // Parses lunch menu from JSON
    void parseLunchMenuData(const QJsonObject data);

    static JSONHandler& getInstance();

signals:
    void jsonDataSent(QMap<QString, QString>);
    void scheduleUrlReceived(const QString);
    void lunchMenuUrlReceived(const QString);
    void personRecognized();

private:
    // JSON data members
    const QString firstName = "firstname";
    const QString lastName = "lastname";

    const QString schedule = "schedule";
    const QString scheduleDay = "day";
    const QString scheduleName = "name";
    const QString scheduleTeacher = "teacher";
    const QString scheduleRoom = "room";
    const QString scheduleStart = "start";
    const QString scheduleEnd = "end";

    const QString foodMenu = "foodMenu";
    const QString foodMenuUrl = "url";

    // From schedule API
    const QString scheduleRawName = "varaus";
    const QString scheduleRawStart = "alku"; // in unix time
    const QString scheduleRawEnd = "loppu"; // in unix time
    const QString scheduleRawTeacher = "opettaja";
    const QString scheduleRawRoom = "tila";

    // From lunch menu API

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
