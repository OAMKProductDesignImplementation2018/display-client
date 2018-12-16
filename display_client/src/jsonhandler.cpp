#include "camera.h"
#include "jsonhandler.h"

#include <QCoreApplication>
#include <QFile>
#include <QTextDocumentFragment>
#include <QXmlStreamReader>

JSONHandler& JSONHandler::getInstance() {
    static JSONHandler instance;
    return instance;
}

void JSONHandler::checkPersonData(const QJsonObject data) {
    if (data.contains("error")) {
        // Person was not detected
        // TODO: implement better error handling
        qDebug() << "Error in detection: " << data;
    }
    else if (data.contains("token")) {
        // When program starts, the software gets token key from Azure api
        // If token is invalid, or there is no token for the device,
        // the api won't return valid data for this device
        parseOrganizationData(data);
    }
    else {
        // Person was successfully detected, remove old pictures and update state
        Camera::removeAllImages();
        emit personRecognized();
        parsePersonData(data);
    }
}

void JSONHandler::parseOrganizationData(const QJsonObject data) {
    qDebug() << "Token received from API";

    // API token
    if (!data.value(tokenId).isNull())
        Organization::getInstance().apiKey = data.value(tokenId).toString();
    // Organization name
    if (!data.value(organizationName).isNull())
        Organization::getInstance().setOrganizationName(data.value(organizationName).toString());
    // Lunch menu data
    if (!data.value(foodMenu).isNull()) {
        // Cast QJsonArray to QJsonObject (there is only one child in the array)
        const auto foodMenuObj = data.value(foodMenu).toArray().at(0).toObject();
        Organization::getInstance().setRestaurantName(foodMenuObj.value(lunchMenuName).toString());
        Organization::getInstance().lunchUrl = foodMenuObj.value(foodMenuUrl).toString();
    }

    // Update idle state
    emit updateIdleStateData();
}

void JSONHandler::parsePersonData(const QJsonObject data) {
    QMap<QString, QString> map;

    // Person's information
    map["target"] = "personData";
    map["firstName"] = data.value(firstName).toString();
    map["lastName"] = data.value(lastName).toString();
    emit jsonDataSent(map);
    map.clear();

    // Schedule url is sent to NetworkManager via signal
    if (!data.value(schedule).isNull())
        emit scheduleUrlReceived(data.value(schedule).toString());

    // Lunch menu
    if (!data.value(foodMenu).isNull()) {
        // Cast array to QJsonObject (there is only one child in the array)
        const auto foodObj = data.value(foodMenu).toArray().at(0).toObject();

        // Diets/allergies etc here

        // Lunch menu url is sent to NetworkManager via signal
        emit lunchMenuUrlReceived(foodObj.value(foodMenuUrl).toString());
    }

    // Notes
    for (const auto notes : data.value(notes).toArray()) {
        QJsonObject noteObj = notes.toObject();

        map["target"] = "notesData";
        map["nTitle"] = noteObj.value(notesTitle).toString();
        map["nContents"] = noteObj.value(notesContent).toString();
        map["nDay"] = noteObj.value(notesDay).toString();
        map["nStart"] = noteObj.value(notesStart).toString();
        map["nEnd"] = noteObj.value(notesEnd).toString();

        emit jsonDataSent(map);
        map.clear();
    }
}

void JSONHandler::parseScheduleData(const QJsonArray data) {
    // Since schedule API returns all upcoming lectures for current period,
    // just get lectures for current week
    const QDate dateNow = QDate::currentDate();

    // Loop through array
    QMap<QString, QString> map;
    for (const auto val : data) {
        const QJsonObject obj = val.toObject();

        // Convert unix time fields to QDateTime
        QDateTime startDate, endDate = QDateTime();
        const unsigned int rawStart = obj.value(scheduleRawStart).toString().toUInt();
        const unsigned int rawEnd = obj.value(scheduleRawEnd).toString().toUInt();
        startDate.setTime_t(rawStart);
        endDate.setTime_t(rawEnd);
        // Skip lectures from other weeks
        if (dateNow.weekNumber() != startDate.date().weekNumber())
            continue;

        // Parse course ID from course name
        const auto scheduleCourseName = obj.value(scheduleRawName).toString().remove(" " + obj.value(scheduleRawId).toString());

        // Put values into QMap
        map["target"] = "scheduleData";
        map["sDay"] = weekDays[startDate.date().dayOfWeek() - 1];
        map["sName"] = scheduleCourseName;
        map["sTeacher"] = obj.value(scheduleRawTeacher).toString();
        map["sRoom"] = obj.value(scheduleRawRoom).toString();
        map["sStart"] = startDate.toString("HH:mm");
        map["sEnd"] = endDate.toString("HH:mm");

        // Send QMap to DataUpdate class which sends them to QML
        emit jsonDataSent(map);
        map.clear();
    }
}

void JSONHandler::parseLunchMenuData(const QJsonObject data) {
    // Parse lunch menu object
    if (data.contains(lunchMenuRaw)) {
        const QJsonArray lunchArr = data.value(lunchMenuRaw).toObject().value(lunchSetMenusRaw).toArray();

        // Clear (possible) previous entries from lunch menu
        emit newLunchMenuDataReceived();

        // Loop through meal types
        QMap<QString, QString> map;
        for (const auto mealType : lunchArr) {
            const QJsonObject mealTypeObj = mealType.toObject();
            map["target"] = "foodData";
            map["fType"] = mealTypeObj.value(lunchNameRaw).toString();

            // Check if there are actually meals in the meal type before emiting the signal
            const QJsonArray mealArray = mealTypeObj.value(lunchMealsRaw).toArray();
            if (!mealArray.isEmpty()) {
                for (const auto meal : mealArray) {
                    const QJsonObject mealObj = meal.toObject();

                    // For future reference, diets are available here
                    /*for (const auto diet : mealObj.value(lunchDietsRaw).toArray()) {
                        qDebug() << "Diet: " << diet.toString();
                    }*/

                    map.insertMulti("fName", mealObj.value(lunchNameRaw).toString());
                }
                emit jsonDataSent(map);
            }
            map.clear();
        }
    }
}

void JSONHandler::parseNewsFeed(const QByteArray data) {
    QXmlStreamReader xml;
    xml.addData(data);

    QString titleString;
    QString contentString;
    QString dateString;
    QString curTag;

    // Clear previous news entries first
    Organization::getInstance().newsContainer.clear();
    // Loop through the XML content
    while (!xml.atEnd()) {
        xml.readNext();

        if (xml.isStartElement()) {
            if (xml.name() == "item")
                contentString = xml.attributes().value("rss:about").toString();

            curTag = xml.name().toString();
        }
        else if (xml.isEndElement()) {
            if (xml.name() == "item") {
                if (contentString.length() >= 5 && !titleString.contains("Yahoo News", Qt::CaseInsensitive))
                    Organization::getInstance().newsContainer.append(QStringList{titleString, contentString, dateString});

                titleString.clear();
                contentString.clear();
                dateString.clear();
            }
        }
        else if (xml.isCharacters() && !xml.isWhitespace()) {
            if (curTag == "title")
                // Parse HTML tags and remove first character from string
                titleString += QTextDocumentFragment::fromHtml(xml.text().toString()).toPlainText();
            else if (curTag == "description")
                // Parse HTML tags and remove first character from string
                contentString += QTextDocumentFragment::fromHtml(xml.text().toString()).toPlainText().remove(0, 1);
            else if (curTag == "pubDate") {
                // Convert pubDate string to DateTime and then back to string
                // Yahoo news are in USA locale
                QLocale dateLocale(QLocale("en_US"));
                QDateTime dateTime = dateLocale.toDateTime(xml.text().toString().split("-").value(0), "ddd, dd MMM yyyy hh:mm:ss ");
                dateString += "(Yahoo, " + dateTime.toString("dd.MM") + ".)";
            }
        }
    }

    if (xml.error() && xml.error() != QXmlStreamReader::PrematureEndOfDocumentError) {
        qDebug() << "XML Error with news feed: " << xml.lineNumber() << " : " << xml.errorString();
    }

    emit newsDataReceived();
}
