#include "camera.h"
#include "dataupdate.h"
#include "jsonhandler.h"
#include <QDebug>

DataUpdate::DataUpdate(QObject *parent) : QObject(parent) {
    stateTimer = new QTimer(this);
    clockTimer = new QTimer(this);

    QObject::connect(&JSONHandler::getInstance(), &JSONHandler::jsonDataSent,
                     this, &DataUpdate::jsonDataReceived);
    QObject::connect(&JSONHandler::getInstance(), &JSONHandler::personRecognized,
                     this, &DataUpdate::showPersonalState);
    QObject::connect(&JSONHandler::getInstance(), &JSONHandler::newLunchMenuDataReceived,
                     this, &DataUpdate::clearLunchMenu);
    QObject::connect(&JSONHandler::getInstance(), &JSONHandler::newsDataReceived,
                     this, &DataUpdate::newsDataReceived);
    QObject::connect(&Organization::getInstance(), &Organization::restaurantNameUpdated,
                     this, &DataUpdate::setRestaurantName);
    QObject::connect(&Organization::getInstance(), &Organization::organizationNameUpdated,
                     this, &DataUpdate::setOrganizationName);

    QObject::connect(stateTimer, &QTimer::timeout,
                     this, &DataUpdate::stateExpired);
    QObject::connect(clockTimer, &QTimer::timeout,
                     this, &DataUpdate::updateTime);

    clockTimer->start(1000);
}

DataUpdate::~DataUpdate() {
    delete stateTimer;
    delete clockTimer;
}

void DataUpdate::updateUI() {
    qDebug() << "DataUpdate::updateUI() responds";
}



bool DataUpdate::getScheduleVisible() const {
    return _scheduleVisible;
}

void DataUpdate::setScheduleVisible(const bool value) {
    _scheduleVisible = value;
    emit scheduleVisibleChanged(value);
}

bool DataUpdate::getFoodMenuVisible() const {
    return _foodMenuVisible;
}

void DataUpdate::setFoodMenuVisible(const bool value) {
    _foodMenuVisible = value;
    emit foodMenuVisibleChanged(value);
}

bool DataUpdate::getNotesVisible() const {
    return _notesVisible;
}

void DataUpdate::setNotesVisible(const bool value) {
    _notesVisible = value;
    emit notesVisibleChanged(value);
}

bool DataUpdate::getNewsVisible() const {
    return _newsVisible;
}

void DataUpdate::setNewsVisible(const bool value) {
    _newsVisible = value;
    emit newsVisibleChanged(value);
}

QString DataUpdate::getDisplayState() const {
    return _displayState;
}

void DataUpdate::setDisplayState(const QString state) {
    _displayState = state;
    emit displayStateChanged(_displayState);
}



QString DataUpdate::firstName() const {
    return _firstName;
}

void DataUpdate::setFirstName(const QString name) {
    _firstName = name;
}

QString DataUpdate::lastName() const {
    return _lastName;
}

void DataUpdate::setLastName(const QString name) {
    _lastName = name;
}

QString DataUpdate::groupID() const {
    return _groupID;
}

void DataUpdate::setGroupID(const QString groupID) {
    _groupID = groupID;
}

QString DataUpdate::organizationName() const {
    return _organizationName;
}

void DataUpdate::setOrganizationName(const QString name) {
    _organizationName = name;
    emit organizationNameChanged();
}

QString DataUpdate::timeString() const {
    return _timeString;
}

void DataUpdate::setTimeString(const QString timeString) {
    _timeString = timeString;
    emit timeUpdated();
}

QString DataUpdate::dateString() const {
    return _dateString;
}

void DataUpdate::setDateString(const QString dateString) {
    _dateString = dateString;
    emit dateUpdated();
}

int DataUpdate::newsCount() const {
    return _newsCount;
}

void DataUpdate::setNewsCount(const int news) {
    _newsCount = news;
    emit newsUpdated();
}

bool DataUpdate::developerMode() const {
    return _developerMode;
}

void DataUpdate::enableDeveloperMode(const bool enable) {
    _developerMode = enable;
    emit developerModeChanged();
}

void DataUpdate::toggleDeveloperMode() {
    enableDeveloperMode(!developerMode());
}

QString DataUpdate::restaurantName() const {
    return _restaurantName;
}

void DataUpdate::setRestaurantName(const QString name) {
    _restaurantName = name;
    emit restaurantNameChanged();
}



// Slots
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
            if (map.contains("sName"))
                vMap.insert("name", map.value("sName"));
            if (map.contains("sTeacher"))
                vMap.insert("teacher", map.value("sTeacher"));
            if (map.contains("sRoom"))
                vMap.insert("room", map.value("sRoom"));
            if (map.contains("sStart")) {
                QStringList timeParts = map.value("sStart").split(":");
                vMap.insert("startH", timeParts.at(0));
                vMap.insert("startM", timeParts.at(1));
            }
            if (map.contains("sEnd")) {
                QStringList timeParts = map.value("sEnd").split(":");
                vMap.insert("endH", timeParts.at(0));
                vMap.insert("endM", timeParts.at(1));
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

        /*else if (map.value("target") == "notesData") {
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
        }*/
    }
}

void DataUpdate::showPersonalState() {
    setDisplayState("Personal");
    stateTimer->start(stateTimerInMSecs);
    Camera::enableCapturing(false);
}

void DataUpdate::stateExpired() {
    stateTimer->stop();
    qDebug() << "State has expired";

    // Remove user's data
    setFirstName("");
    setLastName("");
    setGroupID("");
    emit newsClear();
    emit clearSchedule();
    emit foodMenuClear();

    // Reset to idle state
    setDisplayState("Default");
    Camera::enableCapturing(true);

    emit JSONHandler::getInstance().updateIdleStateData();
}

void DataUpdate::clearLunchMenu() {
    emit foodMenuClear();
}

void DataUpdate::newsDataReceived() {
    // Clear previous entries
    emit newsClear();
    // Let QML know how many news there are
    setNewsCount(Organization::getInstance().newsContainer.size());
    // Emit each news to QML
    for (int i = 0; i < Organization::getInstance().newsContainer.size(); ++i) {
        const auto news = Organization::getInstance().newsContainer[i];
        emit newsAdd(news.value(0), news.value(1), news.value(2));
    }
}

void DataUpdate::updateTime() {
    const auto dateNow = QDateTime::currentDateTime();
    setTimeString(dateNow.toString("hh:mm:ss"));

    const auto dateStr = dateNow.toString("dd.MM.yyyy");
    if (!dateString().contains(dateStr))
        setDateString(dateStr);
}



// Debug functions
void DataUpdate::debugAddScheduleItem() {
    QVariantMap vMap;
    vMap.insert("day", "Ti");
    vMap.insert("name", "Product Design and Implementation");
    vMap.insert("teacher", "Lasse Haverinen");
    vMap.insert("room", "Adobe Connect");
    vMap.insert("startH", "10");
    vMap.insert("startM", "30");
    vMap.insert("endH", "11");
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
