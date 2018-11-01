#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QThreadPool>

#include "testclass.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    // Initialize multithreading
    QThreadPool::globalInstance() -> setMaxThreadCount(QThread::idealThreadCount());
    QGuiApplication app(argc, argv);

    // Register C++ classes for QML
    qmlRegisterType<TestClass>("TestClass", 0, 1, "TestClass");

    // Use QQmlApplicationEngine for
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
