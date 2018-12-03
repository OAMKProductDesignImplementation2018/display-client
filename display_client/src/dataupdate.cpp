#include "dataupdate.h"
#include "jsonhandler.h"
#include <QDebug>

DataUpdate::DataUpdate(QObject *parent) : QObject(parent) {
    _firstName = "Averell";
    _lastName = "Dalton";

    stateTimer = new QTimer(this);

    QObject::connect(&JSONHandler::getInstance(), &JSONHandler::jsonDataSent,
                     this, &DataUpdate::jsonDataReceived);
    QObject::connect(&JSONHandler::getInstance(), &JSONHandler::personRecognized,
                     this, &DataUpdate::showPersonalState);

    QObject::connect(stateTimer, &QTimer::timeout,
                     this, &DataUpdate::stateExpired);
}

DataUpdate::~DataUpdate() {
    delete stateTimer;
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

    if (map.contains("target")) {
        if (map.value("target") == "personData") {
            if (map.contains("firstName")) {
                setFirstName(map.value("firstName"));
                emit firstNameChanged();
            }
            if (map.contains("lastName")) {
                setLastName(map.value("lastName"));
                emit lastNameChanged();
            }
        }

        else if (map.value("target") == "scheduleData") {
            QVariantMap vMap;
            if (map.contains("sDay"))
                vMap.insert("day", map.value("sDay"));
                // qDebug() << map.value("sDay");
            if (map.contains("sName"))
                vMap.insert("name", map.value("sName"));
                // qDebug() << map.value("sName");
            if (map.contains("sTeacher"))
                vMap.insert("teacher", map.value("sTeacher"));
                // qDebug() << map.value("sTeacher");
            if (map.contains("sRoom"))
                vMap.insert("room", map.value("sRoom"));
                // qDebug() << map.value("sRoom");
            if (map.contains("sStart")) {
                QStringList timeParts = map.value("sStart").split(":");
                vMap.insert("startH", timeParts.at(0));
                vMap.insert("startM", timeParts.at(1));
                // qDebug() << map.value("sStart");
            }
            if (map.contains("sEnd")) {
                QStringList timeParts = map.value("sEnd").split(":");
                vMap.insert("endH", timeParts.at(0));
                vMap.insert("endM", timeParts.at(1));
                // qDebug() << map.value("sEnd");
            }

            emit newScheduleEvent(vMap);
        }

        else if (map.value("target") == "foodData") {
            if (map.contains("fType")) {
                QString foods;
                for (const auto &foodName : map.values("fName")) {
                    // Append food name to QString
                    foods.append(foodName);
                    // Add comma if current food is not the last value
                    if (!map.values("fName").at(map.values("fName").size() - 1).contains(foodName))
                        foods.append(", ");
                }
                emit foodMenuAdd(map.value("fType"), foods);
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

void DataUpdate::showPersonalState() {
    setDisplayState("Personal");
    stateTimer->start(stateTimerInMSecs);
}

void DataUpdate::stateExpired() {
    stateTimer->stop();
    qDebug() << "State has expired";

    // Reset to idle state
    // TODO: user's data must be removed!
    setDisplayState("Default");
}


// Debug functions

void DataUpdate::debugAddScheduleItem() {
    QVariantMap vMap;
    vMap.insert("day", "Mon");
    vMap.insert("name", "Name");
    vMap.insert("teacher", "Teacher");
    vMap.insert("room", "Room");
    vMap.insert("startH", "10");
    vMap.insert("startM", "30");
    vMap.insert("endH", "12");
    vMap.insert("endM", "15");

    emit newScheduleEvent(vMap);

    qDebug() << "newScheduleEvent emitted";
}

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
