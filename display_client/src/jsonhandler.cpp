#include "jsonhandler.h"

#include <QFile>
#include <QCoreApplication>

JSONHandler::JSONHandler() {
    dataUpdater = new DataUpdate();
}

JSONHandler::~JSONHandler() {
    delete dataUpdater;
}

void JSONHandler::parseJSON(const QJsonObject data) {

    // Person's information
    qDebug() << "First name: " << data.value("firstName").toString();
    qDebug() << "Last name: " << data.value("lastName").toString();
    qDebug() << "Group ID: " << data.value("groupID").toString();

    // Schedule
    for (const auto schelude : data.value("schedule").toArray())
    {
        QJsonObject scheludeObj = schelude.toObject();
        qDebug() << "Schedule for day " << scheludeObj.value("day").toString() << ":";
        qDebug() << "Course: " << scheludeObj.value("name").toString();
        qDebug() << "Teacher: " << scheludeObj.value("teacher").toString();
        qDebug() << "Room: " << scheludeObj.value("room").toString();
        qDebug() << "Starts at: " << scheludeObj.value("start").toString();
        qDebug() << "Ends at: " << scheludeObj.value("end").toString();
    }

    // Food menu
    for (const auto foodMenu : data.value("foodMenu").toArray())
    {
        QJsonObject menuObj = foodMenu.toObject();
        qDebug() << "Food type is " << menuObj.value("type").toString();

        // Foods for menu type
        for (const auto foods : menuObj.value("menuItems").toArray())
        {
            qDebug() << "Food: " << foods.toObject().value("name").toString();
        }
    }

    // Notes
    for (const auto notes : data.value("notes").toArray())
    {
        QJsonObject noteObj = notes.toObject();
        qDebug() << "Note title: " << noteObj.value("title").toString();
        qDebug() << "Note content: " << noteObj.value("contents").toString();
        qDebug() << "Note day: " << noteObj.value("day").toString();
        qDebug() << "Note starts at: " << noteObj.value("start").toString();
        qDebug() << "Note ends at: " << noteObj.value("end").toString();
    }
}
