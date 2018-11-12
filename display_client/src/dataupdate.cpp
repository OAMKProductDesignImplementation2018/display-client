#include "dataupdate.h"
#include <QDebug>

DataUpdate::DataUpdate(QObject *parent) : QObject(parent) { }


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


// Debug functions

void DataUpdate::debugDisplayStateDefault() {
    setDisplayState("Default");
}

void DataUpdate::debugDisplayStatePersonal() {
    setDisplayState("Personal");
}
