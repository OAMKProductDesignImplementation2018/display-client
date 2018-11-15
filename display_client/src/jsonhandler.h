#ifndef JSONHANDLER_H
#define JSONHANDLER_H

#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QObject>

#include "dataupdate.h"

class JSONHandler : public QObject
{
    Q_OBJECT

public:
    JSONHandler();
    ~JSONHandler();

    void parseJSON(const QJsonObject data);

private:
    DataUpdate *dataUpdater;
};

#endif // JSONHANDLER_H
