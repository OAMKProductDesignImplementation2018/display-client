import QtQuick 2.0
import QtQuick.Controls 2.4

Item {
    property string borderColor: "#3465A4"

    Rectangle {
        anchors.fill: parent

        border.color: borderColor
        color: "white"

        Connections {
            target: dataUpdate

            onNewsClear: {
                newsListModel.clear()
            }

            onNewsAdd: {
                newsListModel.append({"title": title, "desc": desc, "date": date})
            }
        }

        Rectangle {
            id: newsTitleRect
            width: parent.width
            height: parent.height / 13
            color: borderColor

            anchors.top: parent.top
            anchors.left: parent.left

            Text {
                font.pixelSize: 28
                text: "Uutissyötteet"
                color: "white"

                // Dynamic font size
                fontSizeMode: Text.Fit
                width: parent.width
                height: parent.height

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }


        ListModel {
            id: newsListModel
        }

        SwipeView {
            id: newsSlides
            anchors.top: newsTitleRect.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom

            anchors.leftMargin: 5
            anchors.rightMargin: 5
            anchors.bottomMargin: 5

            width: parent.width
            height: parent.height - newsTitleRect.height

            interactive: false

            Repeater {
                model: newsListModel.count

                Loader {
                    active: newsSlides.currentIndex == index
                    sourceComponent: Item {
                        // News title
                        Rectangle {
                            id: newsTitle
                            width: parent.width
                            height: newsTitleRect.height
                            anchors.top: parent.top

                            Text {
                                font.pixelSize: 26
                                text: newsListModel.get(index).title
                                font.bold: true
                                wrapMode: Text.WordWrap

                                // Dynamic font size
                                fontSizeMode: Text.Fit
                                width: parent.width
                                height: parent.height

                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                            }
                        }

                        // News date
                        Rectangle {
                            id: newsDate
                            width: parent.width / 2
                            height: newsTitle.height / 2
                            anchors.top: newsTitle.bottom
                            //anchors.topMargin: 5
                            anchors.right: parent.right
                            anchors.rightMargin: 10

                            visible: dataUpdate.displayState == "Personal"

                            Text {
                                font.pixelSize: 16
                                text: newsListModel.get(index).date
                                wrapMode: Text.WordWrap
                                font.italic: true

                                // Dynamic font size
                                fontSizeMode: Text.Fit
                                width: parent.width
                                height: parent.height

                                horizontalAlignment: Text.AlignRight
                            }
                        }

                        // News content
                        Rectangle {
                            width: parent.width
                            height: {
                                if (newsDate.visible)
                                    parent.height - newsTitle.height - 10 - newsDate.height - 5
                                else
                                    parent.height - newsTitle.height - 10
                            }
                            anchors.top: {
                                if (newsDate.visible)
                                    newsDate.bottom
                                else
                                    newsTitle.bottom
                            }
                            anchors.topMargin: 10
                            anchors.leftMargin: 5
                            anchors.rightMargin: 5

                            Text {
                                font.pixelSize: 18
                                text: newsListModel.get(index).desc
                                wrapMode: Text.WordWrap
                                maximumLineCount: 25
                                elide: Text.ElideRight

                                // Dynamic font size
                                fontSizeMode: Text.Fit
                                width: parent.width
                                height: parent.height

                                horizontalAlignment: Text.AlignHCenter
                            }
                        }
                    }
                }
            }

            Timer {
                id: timerId
                interval: 15000
                running: true
                repeat: true
                onTriggered: {
                    newsSlides.setCurrentIndex(newsSlides.currentIndex + 1)

                    if (newsSlides.currentIndex >= dataUpdate.newsCount)
                        newsSlides.setCurrentIndex(0)
                }
            }
        }
    }
}
