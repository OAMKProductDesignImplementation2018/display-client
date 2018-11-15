#include "jsonhandler.h"

#include <QFile>
#include <QCoreApplication>

JSONHandler::JSONHandler() {
    dataUpdater = new DataUpdate();
}

JSONHandler::~JSONHandler() {
    delete dataUpdater;
}

void JSONHandler::parseJSON(const QJsonObject data) {

    // Loops JSON data through and prints each key and value to debug window
    for (const auto &key : data.keys())
    {
        if (data.value(key).isArray())
        {
            for (const auto key2 : data.value(key).toArray())
            {
                QJsonObject key2object = key2.toObject();
                for (const auto &key2key : key2object.keys())
                {
                    qDebug() << "Sub-key: " << key2key << ", value: " << key2object.value(key2key).toString();
                }
            }
        }
        else
            qDebug() << "Key: " << key << ", value: " << data.value(key).toString();
    }

    // To print certain value by its key
    qDebug() << data.value("lastName").toString();
}

QJsonArray JSONHandler::convertJsonObjectIntoArray(const QJsonObject object) const {
    QJsonArray jsonArray;

    // Loop through QJsonObject
    for (const auto itr : object) {
        if (itr.isObject())
            jsonArray.append(convertJsonObjectIntoArray(itr.toObject()));
        else
            jsonArray.append(itr);
    }
    return jsonArray;
}
