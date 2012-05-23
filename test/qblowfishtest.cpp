#include "qblowfishtest.h"
#include "qblowfish.h"

void QBlowfishTest::blowfishTest_data()
{
    QTest::addColumn<QString>("key");
    QTest::addColumn<QString>("clearText");
    QTest::addColumn<QString>("cipherText");

    // Test vectors by Eric Young
    // from http://www.schneier.com/code/vectors.txt

    QTest::newRow( "1") << "0000000000000000" << "0000000000000000" << "4EF997456198DD78";
    QTest::newRow( "2") << "FFFFFFFFFFFFFFFF" << "FFFFFFFFFFFFFFFF" << "51866FD5B85ECB8A";
    QTest::newRow( "3") << "3000000000000000" << "1000000000000001" << "7D856F9A613063F2";
    QTest::newRow( "4") << "1111111111111111" << "1111111111111111" << "2466DD878B963C9D";
    QTest::newRow( "5") << "0123456789ABCDEF" << "1111111111111111" << "61F9C3802281B096";
    QTest::newRow( "6") << "1111111111111111" << "0123456789ABCDEF" << "7D0CC630AFDA1EC7";
    QTest::newRow( "7") << "FEDCBA9876543210" << "0123456789ABCDEF" << "0ACEAB0FC6A0A28D";
    QTest::newRow( "8") << "7CA110454A1A6E57" << "01A1D6D039776742" << "59C68245EB05282B";
    QTest::newRow( "9") << "0131D9619DC1376E" << "5CD54CA83DEF57DA" << "B1B8CC0B250F09A0";
    QTest::newRow("10") << "07A1133E4A0B2686" << "0248D43806F67172" << "1730E5778BEA1DA4";
    QTest::newRow("11") << "3849674C2602319E" << "51454B582DDF440A" << "A25E7856CF2651EB";
    QTest::newRow("12") << "04B915BA43FEB5B6" << "42FD443059577FA2" << "353882B109CE8F1A";
    QTest::newRow("13") << "0113B970FD34F2CE" << "059B5E0851CF143A" << "48F4D0884C379918";
    QTest::newRow("14") << "0170F175468FB5E6" << "0756D8E0774761D2" << "432193B78951FC98";
    QTest::newRow("15") << "43297FAD38E373FE" << "762514B829BF486A" << "13F04154D69D1AE5";
    QTest::newRow("16") << "07A7137045DA2A16" << "3BDD119049372802" << "2EEDDA93FFD39C79";
    QTest::newRow("17") << "04689104C2FD3B2F" << "26955F6835AF609A" << "D887E0393C2DA6E3";
    QTest::newRow("18") << "37D06BB516CB7546" << "164D5E404F275232" << "5F99D04F5B163969";
    QTest::newRow("19") << "1F08260D1AC2465E" << "6B056E18759F5CCA" << "4A057A3B24D3977B";
    QTest::newRow("20") << "584023641ABA6176" << "004BD6EF09176062" << "452031C1E4FADA8E";
    QTest::newRow("21") << "025816164629B007" << "480D39006EE762F2" << "7555AE39F59B87BD";
    QTest::newRow("22") << "49793EBC79B3258F" << "437540C8698F3CFA" << "53C55F9CB49FC019";
    QTest::newRow("23") << "4FB05E1515AB73A7" << "072D43A077075292" << "7A8E7BFA937E89A3";
    QTest::newRow("24") << "49E95D6D4CA229BF" << "02FE55778117F12A" << "CF9C5D7A4986ADB5";
    QTest::newRow("25") << "018310DC409B26D6" << "1D9D5C5018F728C2" << "D1ABB290658BC778";
    QTest::newRow("26") << "1C587F1C13924FEF" << "305532286D6F295A" << "55CB3774D13EF201";
    QTest::newRow("27") << "0101010101010101" << "0123456789ABCDEF" << "FA34EC4847B268B2";
    QTest::newRow("28") << "1F1F1F1F0E0E0E0E" << "0123456789ABCDEF" << "A790795108EA3CAE";
    QTest::newRow("29") << "E0FEE0FEF1FEF1FE" << "0123456789ABCDEF" << "C39E072D9FAC631D";
    QTest::newRow("30") << "0000000000000000" << "FFFFFFFFFFFFFFFF" << "014933E0CDAFF6E4";
    QTest::newRow("31") << "FFFFFFFFFFFFFFFF" << "0000000000000000" << "F21E9A77B71C49BC";
    QTest::newRow("32") << "0123456789ABCDEF" << "0000000000000000" << "245946885754369A";
    QTest::newRow("33") << "FEDCBA9876543210" << "FFFFFFFFFFFFFFFF" << "6B5C5A9C5D9E0A5A";
}

void QBlowfishTest::blowfishTest()
{
    QFETCH(QString, key);
    QFETCH(QString, clearText);
    QFETCH(QString, cipherText);

    QByteArray keyBytes = QByteArray::fromHex(key.toLatin1());
    QByteArray clearTextBytes = QByteArray::fromHex(clearText.toLatin1());
    QByteArray cipherTextBytes = QByteArray::fromHex(cipherText.toLatin1());

    QBlowfish bf(keyBytes);
    QByteArray encryptedBytes = bf.encrypted(clearTextBytes);
    QVERIFY(cipherTextBytes == encryptedBytes);
    QByteArray decryptedBytes = bf.decrypted(encryptedBytes);
    QVERIFY(clearTextBytes == decryptedBytes);
}

void QBlowfishTest::blowfishTestSameKey_data()
{
    QTest::addColumn<QString>("key");
    QTest::addColumn<QStringList>("clearTextAndCipherText");

    /*
    Test vectors generated using Python Cryptography Toolkit using this code:
    import Crypto
    from Crypto.Cipher import Blowfish
    def generate(key, clear):
        bf = Blowfish.new(key);
        cipher = bf.encrypt(clear);
        print "[" + clear + "]  " + cipher.encode("hex");
    */

    QTest::newRow( "1") << "Caput Draconis"
                        << (QStringList()
                            << "ABCDEFGH" << "ea98b72a1a91af08"
                            << "0123456789abcdef12341234" << "088fc006a93324f99ab889aff84e3c602bf330e8b7d874fe"
                            << "Lorem ipsum dolorsitamet" << "cad01675711bfbfc9e9edc603583e3fc08a54351fc9ad35c"
                            );
}

void QBlowfishTest::blowfishTestSameKey()
{
    QFETCH(QString, key);
    QFETCH(QStringList, clearTextAndCipherText);

    QBlowfish bf1(key.toLatin1());
    bf1.init();

    QBlowfish bf2(key.toLatin1());
    bf2.init();

    for (int i = 0; i < clearTextAndCipherText.count(); i += 2) {
        QByteArray clearText = clearTextAndCipherText.at(i).toLatin1();
        QByteArray cipherText = QByteArray::fromHex(clearTextAndCipherText.at(i + 1).toLatin1());
        QByteArray encrypted = bf1.encrypted(clearText);
        QVERIFY(encrypted == cipherText);
        QByteArray sameInstanceDecrypted = bf1.decrypted(encrypted);
        QVERIFY(sameInstanceDecrypted == clearText);
        QByteArray otherInstanceDecrypted = bf2.decrypted(encrypted);
        QVERIFY(otherInstanceDecrypted == clearText);
    }
}

void QBlowfishTest::blowfishTestPadding_data()
{
    QTest::addColumn<QString>("key");
    QTest::addColumn<QStringList>("clearTexts");

    // Verify that with padding enabled we're able to encrypt/decrypt stuff of any length.
    // The encrypted stuff is not verified, for want of something golden to check with.
    // We only check whether decryption gives us back the original string correctly.

    QTest::newRow("multiples-of-8")
                        << "Caput Draconis"
                        << (QStringList()
                            << "ABCDEFGH"
                            << "0123456789abcdef12341234"
                            << "Lorem ipsum dolorsitamet"
                            );
    QTest::newRow("any-length")
                        << "Lorem ipsum dolor sit amet"
                        << (QStringList()
                            << "Caput Draconis"
                            << "Flibbertigibbet"
                            << "Mimbulus mimbletonia"
                            << "Banana Fritters"
                            << "I Solemly Swear I am up to no good"
                            );
}

void QBlowfishTest::blowfishTestPadding()
{
    QFETCH(QString, key);
    QFETCH(QStringList, clearTexts);

    QBlowfish *bf1 = new QBlowfish(key.toLatin1());
    bf1->setPaddingEnabled(true);

    QList<QByteArray> encryptedBas;
    foreach (const QString &clearText, clearTexts) {
        encryptedBas << bf1->encrypted(clearText.toLatin1());
    }
    delete bf1;

    QBlowfish *bf2 = new QBlowfish(key.toLatin1());
    bf2->setPaddingEnabled(true);

    for (int i = 0; i < encryptedBas.length(); i++) {
        QByteArray encryptedBa = encryptedBas.at(i);
        QByteArray decryptedBa = bf2->decrypted(encryptedBa);
        QVERIFY(decryptedBa == clearTexts.at(i).toLatin1());
    }
    delete bf2;
}

QTEST_MAIN(QBlowfishTest)
