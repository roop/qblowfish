#include <QtCore/QCoreApplication>
#include <QtDebug>
#include "qblowfish.h"

int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    QBlowfish bf(QByteArray::fromHex(QByteArray("0000000000000000")));
    QByteArray clear = QByteArray::fromHex(QByteArray("0000000000000000"));
    qDebug() << "clr:" << clear.toHex();
    QByteArray cipher = bf.encryptBlock(clear);
    qDebug() << "enc:" << cipher.toHex();
    Q_ASSERT(cipher == QByteArray::fromHex(QByteArray("4EF997456198DD78")));
    QByteArray decrypted = bf.decryptBlock(cipher);
    qDebug() << "dec:" << decrypted.toHex();
    Q_ASSERT(decrypted == QByteArray::fromHex(QByteArray("0000000000000000")));
    return 0;
}
