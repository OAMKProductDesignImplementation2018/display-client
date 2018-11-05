#ifndef DATAUPDATE_H
#define DATAUPDATE_H

#include <QObject>

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

signals:

    void scheduleVisibleChanged(bool value);
    void foodMenuVisibleChanged(bool value);
    void notesVisibleChanged(bool value);
    void newsVisibleChanged(bool value);

private:
    bool _scheduleVisible = true;
    bool _foodMenuVisible = true;
    bool _notesVisible = true;
    bool _newsVisible = true;
};

#endif // DATAUPDATE_H
