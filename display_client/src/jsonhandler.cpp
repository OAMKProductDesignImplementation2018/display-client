#include "jsonhandler.h"

#include <QCoreApplication>
#include <QDateTime>
#include <QFile>

JSONHandler& JSONHandler::getInstance() {
    static JSONHandler instance;
    return instance;
}

void JSONHandler::checkPersonData(const QJsonObject data) {
    if (data.contains("error")) {
        // Person was not detected
        // TODO: implement better error handling
        qDebug() << "Error in detection: " << data;
    } else {
        // Person was successfully detected, update state
        emit personRecognized();
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
    // Since schedule API returns all upcoming lectures for current period,
    // just get lectures for current week
    const QDate dateNow = QDate::currentDate();

    // Loop through array
    QMap<QString, QString> map;
    for (const auto val : data) {
        const QJsonObject obj = val.toObject();

        // Convert unix time fields to QDateTime
        QDateTime startDate, endDate = QDateTime();
        const unsigned int rawStart = obj.value(scheduleRawStart).toString().toUInt();
        const unsigned int rawEnd = obj.value(scheduleRawEnd).toString().toUInt();
        startDate.setTime_t(rawStart);
        endDate.setTime_t(rawEnd);
        // Skip lectures from other weeks
        if (dateNow.weekNumber() != startDate.date().weekNumber())
            continue;

        // Put values into QMap
        map["target"] = "scheduleData";
        map["sDay"] = weekDays[startDate.date().dayOfWeek() - 1];
        map["sName"] = obj.value(scheduleRawName).toString();
        map["sTeacher"] = obj.value(scheduleRawTeacher).toString();
        map["sRoom"] = obj.value(scheduleRawRoom).toString();
        map["sStart"] = startDate.toString("HH:mm");
        map["sEnd"] = endDate.toString("HH:mm");

        // Send QMap to DataUpdate class which sends them to QML
        emit jsonDataSent(map);
        map.clear();
    }
}
