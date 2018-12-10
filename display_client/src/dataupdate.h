#ifndef DATAUPDATE_H
#define DATAUPDATE_H

#include <QDateTime>
#include <QMap>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QTimer>
#include <QVariantMap>

class DataUpdate : public QObject {
    Q_OBJECT
public:
    explicit DataUpdate(QObject *parent = nullptr);
    ~DataUpdate();

    Q_INVOKABLE void updateUI();

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
                CONSTANT)
    QString organizationName() const;

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


    // Debug functions
    Q_INVOKABLE void debugDisplayStateDefault();
    Q_INVOKABLE void debugDisplayStatePersonal();

    Q_INVOKABLE void debugFunction();
    Q_INVOKABLE void debugFunction2();

    Q_INVOKABLE void debugAddScheduleItem();

private slots:
    void jsonDataReceived(QMap<QString, QString>);
    void showPersonalState();
    void stateExpired();
    void clearLunchMenu();

    void updateTime();

signals:
    void scheduleVisibleChanged(bool value);
    void foodMenuVisibleChanged(bool value);
    void notesVisibleChanged(bool value);
    void newsVisibleChanged(bool value);
    void displayStateChanged(QString state);

    void newScheduleEvent(QVariantMap vMap);

    void firstNameChanged();
    void lastNameChanged();
    void groupIDChanged();
    void timeUpdated();
    void dateUpdated();

    void foodMenuClear();
    void foodMenuAdd(QString type, QString name);

private:
    bool _scheduleVisible = true;
    bool _foodMenuVisible = true;
    bool _notesVisible = true;
    bool _newsVisible = true;

    QString _displayState = "Default";

    QString _firstName;
    QString _lastName;
    QString _groupID;
    QString _timeString;
    QString _dateString;

    QTimer *stateTimer;
    const int stateTimerInMSecs = 20000; // 20 secs

    QTimer *clockTimer;

    // Organization data
    const QString _organizationName = "OAMK";
};

#endif // DATAUPDATE_H
