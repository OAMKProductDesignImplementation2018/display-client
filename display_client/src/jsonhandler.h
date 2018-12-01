#ifndef JSONHANDLER_H
#define JSONHANDLER_H

#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QMap>
#include <QObject>

#include "dataupdate.h"

class JSONHandler : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(JSONHandler)

public:
    JSONHandler();
    ~JSONHandler();

    // Reads JSON from Azure, checks for errors and checks if person is recognized
    void checkPersonData(const QJsonObject data);
    // Parses person's data from JSON if person was recognized
    void parsePersonData(const QJsonObject data);

    static JSONHandler* getInstance();
    static JSONHandler *_instance;

signals:
    void jsonDataSent(QMap<QString, QString>);
    void scheduleUrlReceived(const QString);

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
    const QString foodMenuItems = "menuItems";
    const QString foodType = "type";
    const QString foodName = "name";

    const QString notes = "notes";
    const QString notesTitle = "title";
    const QString notesContent = "contents";
    const QString notesDay = "day";
    const QString notesStart = "start";
    const QString notesEnd = "end";
};

#endif // JSONHANDLER_H
