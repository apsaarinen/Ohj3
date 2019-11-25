#include <QString>
#include <QtTest>

class default_gameeventhandler : public QObject
{
    Q_OBJECT

public:
    default_gameeventhandler();

private Q_SLOTS:
    void testCase1();
};

default_gameeventhandler::default_gameeventhandler()
{
}

void default_gameeventhandler::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(default_gameeventhandler)

#include "tst_default_gameeventhandler.moc"
