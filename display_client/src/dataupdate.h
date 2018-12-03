#ifndef DATAUPDATE_H
#define DATAUPDATE_H

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

    Q_PROPERTY (QString groupID
                READ groupID
                WRITE setGroupID
                NOTIFY groupIDChanged)
    QString groupID();
    void setGroupID(QString groupID);


    // Debug functions

    Q_INVOKABLE void debugDisplayStateDefault();
    Q_INVOKABLE void debugDisplayStatePersonal();

    Q_INVOKABLE void debugFunction();
    Q_INVOKABLE void debugFunction2();

    Q_INVOKABLE void debugAddScheduleItem();

public slots:
    void jsonDataReceived(QMap<QString, QString>);
    void showPersonalState();
    void stateExpired();

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

    QTimer *stateTimer;
    const int stateTimerInMSecs = 20000; // 20 secs
};

#endif // DATAUPDATE_H
