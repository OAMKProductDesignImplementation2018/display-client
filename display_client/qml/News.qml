import QtQuick 2.0

Item {
    Rectangle {
        id: debugBox
        anchors.fill: parent

        border.color: "#000000"
        color: "#FFFFFF"

//        Text {
//            id: newsItemText
//            anchors.centerIn: parent
//            font.pixelSize: 24
//            text: "News Item"
//            horizontalAlignment: Text.AlignHCenter
//        }
    }

    ListModel {
        id: newsListModel

        ListElement {
            title: "News Item 1"
            contents: "Yhteinen kampus - kaksi itsenäistä korkeakoulua"
        }

        ListElement {
            title: "News Item 2"
            contents: "OAMK on merkittävä alueellinen työ- ja elinkeinoelämän kumppani ja uudistaja"
        }

        ListElement {
            title: "News Item 3"
            contents: "Yhteiskampus on mahdollisuus Oamkille ja koko Oululle"
        }

        ListElement {
            title: "News Item 4"
            contents: "Jäitä hattuun kampusselvityksessä!"
        }
    }

    ListView {
        id: newsList
        anchors.fill: parent
        orientation: ListView.Vertical
        model: newsListModel
        interactive: false

        delegate: Rectangle {
            width: parent.width
            height: newsList.height / newsListModel.count
            color: index % 2 ? "#FFDCA2" : "#FFEFD5"
            border.color: "#4d3000"

            Text {
                id: newsTitle
                x: 6
                y: 4
                font.pixelSize: 21
                text: title
            }

            Text {
                id: newsContent
                x: 4
                anchors.top: newsTitle.bottom
                anchors.topMargin: 4
                width: parent.width - 4
                clip: true
                maximumLineCount: {
                    if (newsListModel.count > 6) { 1 }
                    else if (newsListModel.count > 4) { 2 }
                    else { 3 }
                }
                elide: Text.ElideRight
                wrapMode: Text.WordWrap
                font.pixelSize: {
                    if (newsListModel.count > 6) { 14 }
                    else if (newsListModel.count > 4) { 16 }
                    else { 18 }
                }

                text: contents
            }
        }
    }
}
