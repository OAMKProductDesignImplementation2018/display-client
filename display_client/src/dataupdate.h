#ifndef DATAUPDATE_H
#define DATAUPDATE_H

#include <QObject>
#include <QString>
#include <QStringList>

class DataUpdate : public QObject {
    Q_OBJECT
public:
    explicit DataUpdate(QObject *parent = nullptr);

    Q_INVOKABLE void updateUI();

    Q_PROPERTY (bool scheduleVisible
                MEMBER _scheduleVisible
                READ getScheduleVisible
                WRITE setScheduleVisible
                NOTIFY scheduleVisibleChanged)
    bool getScheduleVisible();
    void setScheduleVisible(bool value);

    Q_PROPERTY (bool foodMenuVisible
                MEMBER _foodMenuVisible
                READ getFoodMenuVisible
                WRITE setFoodMenuVisible
                NOTIFY foodMenuVisibleChanged)
    bool getFoodMenuVisible();
    void setFoodMenuVisible(bool value);

    Q_PROPERTY (bool notesVisible
                MEMBER _notesVisible
                READ getNotesVisible
                WRITE setNotesVisible
                NOTIFY notesVisibleChanged)
    bool getNotesVisible();
    void setNotesVisible(bool value);

    Q_PROPERTY (bool newsVisible
                MEMBER _newsVisible
                READ getNewsVisible
                WRITE setNewsVisible
                NOTIFY newsVisibleChanged)
    bool getNewsVisible();
    void setNewsVisible(bool value);

    Q_PROPERTY (QString displayState
                MEMBER _displayState
                READ getDisplayState
                WRITE setDisplayState
                NOTIFY displayStateChanged)
    QString getDisplayState();
    void setDisplayState(QString state);


    Q_PROPERTY (QStringList scheduleMonday
                MEMBER _scheduleMon
                READ getScheduleMonday
                WRITE setScheduleMonday
                NOTIFY scheduleChanged)
    QStringList getScheduleMonday();
    void setScheduleMonday(QStringList scheduleMonday);

    Q_PROPERTY (QStringList scheduleTuesday
                MEMBER _scheduleTue
                READ getScheduleTuesday
                WRITE setScheduleTuesday
                NOTIFY scheduleChanged)
    QStringList getScheduleTuesday();
    void setScheduleTuesday(QStringList scheduleTuesday);

    Q_PROPERTY (QStringList scheduleWednesday
                MEMBER _scheduleWed
                READ getScheduleWednesday
                WRITE setScheduleWednesday
                NOTIFY scheduleChanged)
    QStringList getScheduleWednesday();
    void setScheduleWednesday(QStringList scheduleWednesday);

    Q_PROPERTY (QStringList scheduleThursday
                MEMBER _scheduleThu
                READ getScheduleThursday
                WRITE setScheduleThursday
                NOTIFY scheduleChanged)
    QStringList getScheduleThursday();
    void setScheduleThursday(QStringList scheduleThursday);

    Q_PROPERTY (QStringList scheduleFriday
                MEMBER _scheduleFri
                READ getScheduleFriday
                WRITE setScheduleFriday
                NOTIFY scheduleChanged)
    QStringList getScheduleFriday();
    void setScheduleFriday(QStringList scheduleFriday);


    Q_PROPERTY (QString firstName
                READ firstName
                WRITE setFirstName
                NOTIFY firstNameChanged)
    QString firstName();
    void setFirstName(QString firstName);

    Q_PROPERTY (QString lastName
                READ lastName
                WRITE setLastName
                NOTIFY lastNameChanged)
    QString lastName();
    void setLastName(QString lastName);



    // Debug functions

    Q_INVOKABLE void debugDisplayStateDefault();
    Q_INVOKABLE void debugDisplayStatePersonal();

    Q_INVOKABLE void debugFunction();
    Q_INVOKABLE void debugFunction2();


signals:

    void scheduleVisibleChanged(bool value);
    void foodMenuVisibleChanged(bool value);
    void notesVisibleChanged(bool value);
    void newsVisibleChanged(bool value);
    void displayStateChanged(QString state);

    void scheduleChanged();

    void firstNameChanged();
    void lastNameChanged();

    void foodMenuClear();
    void foodMenuAdd(QString type, QString name);


private:
    bool _scheduleVisible = true;
    bool _foodMenuVisible = true;
    bool _notesVisible = true;
    bool _newsVisible = true;

    QString _displayState = "Default";

    QStringList _scheduleMon;
    QStringList _scheduleTue;
    QStringList _scheduleWed;
    QStringList _scheduleThu;
    QStringList _scheduleFri;

    QString _firstName;
    QString _lastName;

};

#endif // DATAUPDATE_H
