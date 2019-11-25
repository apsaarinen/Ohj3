#include <QString>
#include <QtTest>

class Gameengine_testsTest : public QObject
{
    Q_OBJECT

public:
    Gameengine_testsTest();

private Q_SLOTS:
    void testCase1();
};

Gameengine_testsTest::Gameengine_testsTest()
{
}

void Gameengine_testsTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(Gameengine_testsTest)

#include "tst_gameengine_teststest.moc"
