#include "jsonhandler.h"

#include <QCoreApplication>
#include <QDateTime>
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
    if (data.contains("error")) {
        // Person was not detected
        // TODO: implement better error handling
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

    // Schedule url is sent to NetworkManager via signal
    if (!data.value(schedule).isNull())
        emit scheduleUrlReceived(data.value(schedule).toString());

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

void JSONHandler::parseScheduleData(const QJsonArray data) {
    // Loop through array
    for (const auto val : data) {
        const QJsonObject obj = val.toObject();

        qDebug() << "Item: " << obj.value(scheduleRawRoom).toString();
        qDebug() << "Room is: " << obj.value(scheduleRawRoom).toString();
        qDebug() << "Teacher is: " << obj.value(scheduleRawTeacher).toString();

        // Convert unix time fields to "readable" date
        QDateTime startDate = QDateTime();
        QDateTime endDate = QDateTime();

        unsigned int rawStart = obj.value(scheduleRawStart).toString().toUInt();
        unsigned int rawEnd = obj.value(scheduleRawEnd).toString().toUInt();
        startDate.setTime_t(rawStart);
        endDate.setTime_t(rawEnd);

        qDebug() << "Start time: " << startDate;
        qDebug() << "End time: " << endDate;
    }
}
