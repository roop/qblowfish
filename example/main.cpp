#include <QtCore/QCoreApplication>
#include <QFile>
#include <QtDebug>
#include "qblowfish.h"

// Random key generated at http://www.random.org/bytes/
#define KEY_HEX "ea462947a76af8a50dba0ad01455c8c3"

int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    QBlowfish bf(QByteArray::fromHex(KEY_HEX));

    // Encrypt string
    bf.setPaddingEnabled(true); // Enable padding to be able to encrypt an arbitrary length of bytes
    QString clearText("Balderdash");
    QByteArray cipherText = bf.encrypted(clearText.toUtf8());
    qDebug() << "Encrypted ba (hex):" << cipherText.toHex();

    // Encrypt a file
    QFile clearFile("clearText.txt");
    if (!clearFile.open(QFile::ReadOnly)) {
        qFatal("Could not open clearText.txt for reading");
    }
    QFile encryptedFile("encrypted.dat");
    if (!encryptedFile.open(QFile::WriteOnly)) {
        qFatal("Could not open encrypted.dat for writing");
    }
    qint64 encryptedBytesWritten = 0;
    while (!clearFile.atEnd()) {
        QByteArray data = clearFile.read(8); // Let's process the file in 8-byte blocks (can use any multiple of 8)
        bf.setPaddingEnabled((clearFile.size() - encryptedBytesWritten) <= 8); // Enable padding for the last block only
        QByteArray encryptedData = bf.encrypted(data);
        Q_ASSERT(encryptedData.size() == 8);
        qint64 bytesWritten = encryptedFile.write(encryptedData);
        encryptedBytesWritten += bytesWritten;
    }
    encryptedFile.close();
    clearFile.close();
    qDebug() << "Encrypted data written to encrypted.dat";

    // Decrypt string
    bf.setPaddingEnabled(true);
    QByteArray decryptedBa = bf.decrypted(cipherText);
    QString decryptedString = QString::fromUtf8(decryptedBa.constData(), decryptedBa.size());
    qDebug() << "Decrypted string:" << decryptedString;

    // Decrypt file
    bf.setPaddingEnabled(false);
    QFile encryptedFile2("encrypted.dat");
    if (!encryptedFile2.open(QFile::ReadOnly)) {
        qFatal("Could not open encrypted.dat for reading");
    }
    QFile decryptedFile("decrypted.txt");
    if (!decryptedFile.open(QFile::WriteOnly)) {
        qFatal("Could not open decrypted.txt for writing");
    }
    qint64 decryptedBytesWritten = 0;
    while (!encryptedFile2.atEnd()) {
        QByteArray data = encryptedFile2.read(8); // Let's process the file in 8-byte blocks (can use any multiple of 8)
        bf.setPaddingEnabled((encryptedFile2.size() - decryptedBytesWritten) <= 8); // Enable padding for the last block only
        QByteArray decryptedData = bf.decrypted(data);
        Q_ASSERT(decryptedData.size() <= 8);
        qint64 bytesWritten = decryptedFile.write(decryptedData);
        decryptedBytesWritten += bytesWritten;
    }
    decryptedFile.close();
    encryptedFile2.close();
    qDebug() << "Decrypted data written to decrypted.txt";

    return 0;
}
