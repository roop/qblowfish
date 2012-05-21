#ifndef QBLOWFISH_H
#define QBLOWFISH_H

#include <QByteArray>

class QBlowfish
{
public:
    QBlowfish(const QByteArray &key);
    bool init();

    // encrypt/decrypt 8 bytes of data
    QByteArray encryptBlock(const QByteArray &clearText);
    QByteArray decryptBlock(const QByteArray &cipherText);

private:
    // core encrypt/decrypt methods
    void coreEncrypt(char *x);
    void coreDecrypt(char *x);

    QByteArray m_key;
    bool m_initialized;
    QByteArray m_parray;
    QByteArray m_sbox1, m_sbox2, m_sbox3, m_sbox4;
};

#endif // QBLOWFISH_H
