#include <QtCore/QCoreApplication>
#include <QtDebug>
#include "qblowfish.h"

int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    QBlowfish bf;
    bf.init(QByteArray::fromHex(QByteArray("0000000000000000")));
    QByteArray clear = QByteArray::fromHex(QByteArray("0000000000000000"));
    qDebug() << "clr:" << clear.toHex();
    bf.coreEncrypt(clear.data());
    qDebug() << "enc:" << clear.toHex();
    Q_ASSERT(clear == QByteArray::fromHex(QByteArray("4EF997456198DD78")));
    bf.coreDecrypt(clear.data());
    qDebug() << "dec:" << clear.toHex();
    Q_ASSERT(clear == QByteArray::fromHex(QByteArray("0000000000000000")));
    return 0;
}
