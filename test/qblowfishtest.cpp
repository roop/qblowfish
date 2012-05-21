#include "qblowfishtest.h"
#include "qblowfish.h"

void QBlowfishTest::blowfishTest()
{
    QByteArray key = QByteArray::fromHex("0000000000000000");
    QByteArray clearText = QByteArray::fromHex("0000000000000000");
    QByteArray encrypted = QByteArray::fromHex("4EF997456198DD78");

    QBlowfish bf(key);
    QByteArray cipher = bf.encrypt(clearText);
    QVERIFY(cipher == encrypted);
    QByteArray original = bf.decrypt(cipher);
    QVERIFY(original == clearText);
}

QTEST_MAIN(QBlowfishTest)
