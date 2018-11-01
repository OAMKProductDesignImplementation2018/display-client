#include "testclass.h"
#include <QDebug>

TestClass::TestClass() {
    testValue = 3;
}

TestClass::~TestClass() {

}

void TestClass::testFunction() {
    emit testSignalEmitted();
    qDebug() << "Signal emitted. Test value: " << testValue;
}
