#include "dataupdate.h"
#include "jsonhandler.h"
#include <QDebug>

DataUpdate::DataUpdate(QObject *parent) : QObject(parent) {
    _firstName = "Averell";
    _lastName = "Dalton";

    QObject::connect(JSONHandler::getInstance(), SIGNAL(jsonDataSent(QMap<QString, QString>)),
                     this, SLOT(jsonDataReceived(QMap<QString, QString>)));
}


void DataUpdate::updateUI() {
    qDebug() << "DataUpdate::updateUI() responds";
}


bool DataUpdate::getScheduleVisible() {
    return _scheduleVisible;
}

void DataUpdate::setScheduleVisible(bool value) {
    _scheduleVisible = value;
    emit scheduleVisibleChanged(value);
}

bool DataUpdate::getFoodMenuVisible() {
    return _foodMenuVisible;
}

void DataUpdate::setFoodMenuVisible(bool value) {
    _foodMenuVisible = value;
    emit foodMenuVisibleChanged(value);
}

bool DataUpdate::getNotesVisible() {
    return _notesVisible;
}

void DataUpdate::setNotesVisible(bool value) {
    _notesVisible = value;
    emit notesVisibleChanged(value);
}

bool DataUpdate::getNewsVisible() {
    return _newsVisible;
}

void DataUpdate::setNewsVisible(bool value) {
    _newsVisible = value;
    emit newsVisibleChanged(value);
}

QString DataUpdate::getDisplayState() {
    return _displayState;
}

void DataUpdate::setDisplayState(QString state) {
    _displayState = state;
    emit displayStateChanged(_displayState);
}






QStringList DataUpdate::getScheduleMonday() {
    return _scheduleMon;
}

void DataUpdate::setScheduleMonday(QStringList monday) {
    _scheduleMon = monday;
}


QStringList DataUpdate::getScheduleTuesday() {
    return _scheduleTue;
}

void DataUpdate::setScheduleTuesday(QStringList tuesday) {
    _scheduleTue = tuesday;
}

QStringList DataUpdate::getScheduleWednesday() {
    return _scheduleWed;
}

void DataUpdate::setScheduleWednesday(QStringList wednesday) {
    _scheduleWed = wednesday;
}

QStringList DataUpdate::getScheduleThursday() {
    return _scheduleThu;
}

void DataUpdate::setScheduleThursday(QStringList thursday) {
    _scheduleWed = thursday;
}

QStringList DataUpdate::getScheduleFriday() {
    return _scheduleFri;
}

void DataUpdate::setScheduleFriday(QStringList friday) {
    _scheduleWed = friday;
}


QString DataUpdate::firstName() {
    return _firstName;
}

void DataUpdate::setFirstName(QString name) {
    _firstName = name;
}

QString DataUpdate::lastName() {
    return _lastName;
}

void DataUpdate::setLastName(QString name) {
    _lastName = name;
}

QString DataUpdate::groupID() {
    return _groupID;
}

void DataUpdate::setGroupID(QString groupID) {
    _groupID = groupID;
}




// Public slots

void DataUpdate::jsonDataReceived(QMap<QString, QString> map) {
    // qDebug() << map;
    if (map.contains("target")) {
        if (map.value("target") == "personData") {
            if (map.contains("firstName"))
                setFirstName(map.value("firstName"));
            if (map.contains("lastName"))
                setLastName(map.value("lastName"));
            if (map.contains("groupID"))
                setGroupID(map.value("groupID"));
        }

        else if (map.value("target") == "scheduleData") {
            if (map.contains("sDay"))
                qDebug() << map.value("sDay");
            if (map.contains("sName"))
                qDebug() << map.value("sName");
            if (map.contains("sTeacher"))
                qDebug() << map.value("sTeacher");
            if (map.contains("sRoom"))
                qDebug() << map.value("sRoom");
            if (map.contains("sStart"))
                qDebug() << map.value("sStart");
            if (map.contains("sEnd"))
                qDebug() << map.value("sEnd");
        }

        else if (map.value("target") == "foodData") {
            if (map.contains("fType")) {
                qDebug() << map.value("fType");
                qDebug() << map.values("fName");
            }
        }

        else if (map.value("target") == "notesData") {
            if (map.contains("nTitle"))
                qDebug() << map.value("nTitle");
            if (map.contains("nContents"))
                qDebug() << map.value("nContents");
            if (map.contains("nDay"))
                qDebug() << map.value("nDay");
            if (map.contains("nStart"))
                qDebug() << map.value("nStart");
            if (map.contains("nEnd"))
                qDebug() << map.value("nEnd");
        }
    }
}


// Debug functions

void DataUpdate::debugDisplayStateDefault() {
    setDisplayState("Default");
}

void DataUpdate::debugDisplayStatePersonal() {
    setDisplayState("Personal");
}

void DataUpdate::debugFunction() {
    emit foodMenuClear();
}

void DataUpdate::debugFunction2() {
    emit foodMenuAdd("Lunch", "Oolated Squiggs");
}
