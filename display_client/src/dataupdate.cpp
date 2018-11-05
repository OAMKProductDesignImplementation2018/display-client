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
