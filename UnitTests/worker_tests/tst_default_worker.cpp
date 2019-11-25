#include <QString>
#include <QtTest>

class default_worker : public QObject
{
    Q_OBJECT

public:
    default_worker();

private Q_SLOTS:
    void testCase1();
};

default_worker::default_worker()
{
}

void default_worker::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(default_worker)

#include "tst_default_worker.moc"
