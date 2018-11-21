#include "jsonhandler.h"

#include <QCoreApplication>
#include <QFile>

JSONHandler::JSONHandler() { }
JSONHandler::~JSONHandler() { }

JSONHandler* JSONHandler::_instance = nullptr;
JSONHandler* JSONHandler::getInstance() {
    if(!_instance)
        _instance = new JSONHandler();
    return _instance;
}

void JSONHandler::parseJSON(const QJsonObject data) {

    // Person's information

    QMap<QString, QString> map;

    map["firstName"] = data.value("firstName").toString();
    map["lastName"] = data.value("lastName").toString();
    map["groupID"] = data.value("groupID").toString();

    emit jsonDataSent(map);
    map.clear();

    // Schedule
    for (const auto schelude : data.value("schedule").toArray()) {
        QJsonObject scheludeObj = schelude.toObject();

        map["sDay"] = scheludeObj.value("day").toString();
        map["sName"] = scheludeObj.value("name").toString();
        map["sTeacher"] = scheludeObj.value("teacher").toString();
        map["sRoom"] = scheludeObj.value("room").toString();
        map["sStart"] = scheludeObj.value("start").toString();
        map["sEnd"] = scheludeObj.value("end").toString();

        emit jsonDataSent(map);
        map.clear();
    }

    // Food menu
    for (const auto foodMenu : data.value("foodMenu").toArray()) {
        QJsonObject menuObj = foodMenu.toObject();
        QString keyName = "fName";
        int iterator = 0;

        map["fType"] = menuObj.value("type").toString();

        // Foods for menu type
        for (const auto foods : menuObj.value("menuItems").toArray()) {
            map["fName" + QString::number(iterator)] = foods.toObject().value("name").toString();

            iterator++;
        }

        emit jsonDataSent(map);
        map.clear();
    }

    // Notes
    for (const auto notes : data.value("notes").toArray()) {
        QJsonObject noteObj = notes.toObject();

        map["nTitle"] = noteObj.value("title").toString();
        map["nContents"] = noteObj.value("contents").toString();
        map["nDay"] = noteObj.value("day").toString();
        map["nStart"] = noteObj.value("start").toString();
        map["nEnd"] = noteObj.value("end").toString();

        emit jsonDataSent(map);
        map.clear();
    }
}
