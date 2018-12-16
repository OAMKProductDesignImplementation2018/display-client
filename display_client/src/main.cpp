#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QThreadPool>

#include "camera.h"
#include "dataupdate.h"
#include "networkmanager.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    // Window title
    QCoreApplication::setApplicationName("NoticeMe!");

    // Initialize multithreading
    QThreadPool::globalInstance() -> setMaxThreadCount(QThread::idealThreadCount());
    QGuiApplication app(argc, argv);

    // Register C++ classes for QML
    qmlRegisterType<DataUpdate>("DataUpdate", 0, 1, "DataUpdate");
    qmlRegisterType<Camera>("CaptureImage", 0, 1, "CaptureImage");
    qmlRegisterType<NetworkManager>("NetworkManager", 0, 1, "NetworkManager");

    // Use QQmlApplicationEngine for
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
