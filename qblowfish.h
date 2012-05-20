#ifndef QBLOWFISH_H
#define QBLOWFISH_H

#include <QByteArray>

class QBlowfish
{
public:
    QBlowfish();
    void init(const QByteArray &key);
    void coreEncrypt(char *x);
    void coreDecrypt(char *x);
private:
    QByteArray m_parray;
    QByteArray m_sbox1, m_sbox2, m_sbox3, m_sbox4;
};

#endif // QBLOWFISH_H
