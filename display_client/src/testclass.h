#ifndef TESTCLASS_H
#define TESTCLASS_H

#include <QObject>


class TestClass : public QObject {
    Q_OBJECT

public:
    TestClass();
    ~TestClass();

    Q_INVOKABLE void testFunction();

signals:
    void testSignalEmitted();

private:
    int testValue;
};

#endif // TESTCLASS_H
