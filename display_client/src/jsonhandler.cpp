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

void JSONHandler::checkPersonData(const QJsonObject data) {
    if (!data.contains(firstName) ||
        !data.contains(lastName) ||
        !data.contains(schedule) ||
        !data.contains(foodMenu) ||
        !data.contains(notes)) {
        // Person was not detected
        // TODO: implement better error check and handling
        qDebug() << "Error in detection: " << data;
    } else {
        // Person was successfully detected
        parsePersonData(data);
    }
}

void JSONHandler::parsePersonData(const QJsonObject data) {
    QMap<QString, QString> map;

    // Person's information
    map["target"] = "personData";
    map["firstName"] = data.value(firstName).toString();
    map["lastName"] = data.value(lastName).toString();

    emit jsonDataSent(map);
    map.clear();

    // Schedule
    for (const auto schelude : data.value(schedule).toArray()) {
        QJsonObject scheludeObj = schelude.toObject();

        map["target"] = "scheduleData";
        map["sDay"] = scheludeObj.value(scheduleDay).toString();
        map["sName"] = scheludeObj.value(scheduleName).toString();
        map["sTeacher"] = scheludeObj.value(scheduleTeacher).toString();
        map["sRoom"] = scheludeObj.value(scheduleRoom).toString();
        map["sStart"] = scheludeObj.value(scheduleStart).toString();
        map["sEnd"] = scheludeObj.value(scheduleEnd).toString();

        emit jsonDataSent(map);
        map.clear();
    }

    // Food menu
    for (const auto foodMenu : data.value(foodMenu).toArray()) {
        QJsonObject menuObj = foodMenu.toObject();

        map["target"] = "foodData";
        map["fType"] = menuObj.value(foodType).toString();

        // Foods for menu type
        for (const auto foods : menuObj.value(foodMenuItems).toArray()) {
            map.insertMulti("fName", foods.toObject().value(foodName).toString());
        }

        emit jsonDataSent(map);
        map.clear();
    }

    // Notes
    for (const auto notes : data.value(notes).toArray()) {
        QJsonObject noteObj = notes.toObject();

        map["target"] = "notesData";
        map["nTitle"] = noteObj.value(notesTitle).toString();
        map["nContents"] = noteObj.value(notesContent).toString();
        map["nDay"] = noteObj.value(notesDay).toString();
        map["nStart"] = noteObj.value(notesStart).toString();
        map["nEnd"] = noteObj.value(notesEnd).toString();

        emit jsonDataSent(map);
        map.clear();
    }
}
