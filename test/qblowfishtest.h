#ifndef QBLOWFISHTEST_H
#define QBLOWFISHTEST_H

#include <QObject>
#include <QtTest/QtTest>

class QBlowfishTest: public QObject
{
    Q_OBJECT
private slots:
    void blowfishTest_data();
    void blowfishTest();
    void blowfishTestSameKey_data();
    void blowfishTestSameKey();
};

#endif // QBLOWFISHTEST_H
