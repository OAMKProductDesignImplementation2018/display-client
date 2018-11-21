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
    Q_DISABLE_COPY(JSONHandler)

public:
    JSONHandler();
    ~JSONHandler();

    void parseJSON(const QJsonObject data);

    static JSONHandler* getInstance();
    static JSONHandler *_instance;

private:

};

#endif // JSONHANDLER_H
