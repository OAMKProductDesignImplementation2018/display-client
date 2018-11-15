#include "jsonhandler.h"

JSONHandler::JSONHandler() {
    dataUpdater = new DataUpdate();
}

JSONHandler::~JSONHandler() {
    delete dataUpdater;
}

void JSONHandler::parseJSON(const QJsonObject data) {
    // Convert object into array
    QJsonArray jsonArray = convertJsonObjectIntoArray(data);

    qDebug() << jsonArray;
    qDebug() << jsonArray[2].toString();
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
