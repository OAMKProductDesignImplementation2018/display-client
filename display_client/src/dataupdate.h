#ifndef DATAUPDATE_H
#define DATAUPDATE_H

#include <QDateTime>
#include <QMap>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QTimer>
#include <QVariantMap>

#include "organization.h"

class DataUpdate : public QObject {
    Q_OBJECT
public:
    explicit DataUpdate(QObject *parent = nullptr);
    ~DataUpdate();

    Q_INVOKABLE void updateUI();
    Q_INVOKABLE void stateExpired();

    Q_PROPERTY (bool scheduleVisible
                MEMBER _scheduleVisible
                READ getScheduleVisible
                WRITE setScheduleVisible
                NOTIFY scheduleVisibleChanged)
    bool getScheduleVisible() const;
    void setScheduleVisible(const bool value);

    Q_PROPERTY (bool foodMenuVisible
                MEMBER _foodMenuVisible
                READ getFoodMenuVisible
                WRITE setFoodMenuVisible
                NOTIFY foodMenuVisibleChanged)
    bool getFoodMenuVisible() const;
    void setFoodMenuVisible(const bool value);

    Q_PROPERTY (bool notesVisible
                MEMBER _notesVisible
                READ getNotesVisible
                WRITE setNotesVisible
                NOTIFY notesVisibleChanged)
    bool getNotesVisible() const;
    void setNotesVisible(const bool value);

    Q_PROPERTY (bool newsVisible
                MEMBER _newsVisible
                READ getNewsVisible
                WRITE setNewsVisible
                NOTIFY newsVisibleChanged)
    bool getNewsVisible() const;
    void setNewsVisible(const bool value);

    Q_PROPERTY (QString displayState
                MEMBER _displayState
                READ getDisplayState
                WRITE setDisplayState
                NOTIFY displayStateChanged)
    QString getDisplayState() const;
    void setDisplayState(const QString state);


    Q_PROPERTY (QString firstName
                READ firstName
                WRITE setFirstName
                NOTIFY firstNameChanged)
    QString firstName() const;
    void setFirstName(const QString firstName);

    Q_PROPERTY (QString lastName
                READ lastName
                WRITE setLastName
                NOTIFY lastNameChanged)
    QString lastName() const;
    void setLastName(const QString lastName);

    Q_PROPERTY (QString groupID
                READ groupID
                WRITE setGroupID
                NOTIFY groupIDChanged)
    QString groupID() const;
    void setGroupID(const QString groupID);

    Q_PROPERTY (QString organizationName
                READ organizationName
                WRITE setOrganizationName
                NOTIFY organizationNameChanged)
    QString organizationName() const;
    void setOrganizationName(const QString name);

    Q_PROPERTY (QString timeString
                READ timeString
                WRITE setTimeString
                NOTIFY timeUpdated)
    QString timeString() const;
    void setTimeString(const QString timeString);

    Q_PROPERTY (QString dateString
                READ dateString
                WRITE setDateString
                NOTIFY dateUpdated)
    QString dateString() const;
    void setDateString(const QString dateString);

    Q_PROPERTY (int newsCount
                READ newsCount
                WRITE setNewsCount
                NOTIFY newsUpdated)
    int newsCount() const;
    void setNewsCount(const int news);

    Q_PROPERTY (bool developerMode
                MEMBER _developerMode
                READ developerMode
                WRITE enableDeveloperMode
                NOTIFY developerModeChanged)
    bool developerMode() const;
    void enableDeveloperMode(const bool enable);
    Q_INVOKABLE void toggleDeveloperMode();

    Q_PROPERTY (QString restaurantName
                READ restaurantName
                WRITE setRestaurantName
                NOTIFY restaurantNameChanged)
    QString restaurantName() const;
    void setRestaurantName(const QString name);


    // Debug functions
    Q_INVOKABLE void debugDisplayStateDefault();
    Q_INVOKABLE void debugDisplayStatePersonal();
    Q_INVOKABLE void debugAddScheduleItem();

private slots:
    void jsonDataReceived(QMap<QString, QString>);
    void showPersonalState();
    void clearLunchMenu();
    void newsDataReceived();

    void updateTime();

signals:
    void scheduleVisibleChanged(bool value);
    void foodMenuVisibleChanged(bool value);
    void notesVisibleChanged(bool value);
    void newsVisibleChanged(bool value);
    void displayStateChanged(QString state);

    void newScheduleEvent(QVariantMap vMap);
    void clearSchedule();

    void firstNameChanged();
    void lastNameChanged();
    void groupIDChanged();
    void organizationNameChanged();
    void timeUpdated();
    void dateUpdated();
    void newsUpdated();
    void developerModeChanged();
    void restaurantNameChanged();

    void foodMenuClear();
    void foodMenuAdd(QString type, QString name);
    void newsClear();
    void newsAdd(QString title, QString desc, QString date);

private:
    bool _scheduleVisible = true;
    bool _foodMenuVisible = true;
    bool _notesVisible = true;
    bool _newsVisible = true;
    bool _developerMode = false;

    QString _displayState = "Default";

    QString _firstName;
    QString _lastName;
    QString _groupID;
    QString _timeString;
    QString _dateString;
    int _newsCount;
    QString _restaurantName;
    QString _organizationName;

    QTimer *stateTimer;
    const int stateTimerInMSecs = 20000; // 20 secs

    QTimer *clockTimer;
};

#endif // DATAUPDATE_H
