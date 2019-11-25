#include <QString>
#include <QtTest>

class default_objectmanager : public QObject
{
    Q_OBJECT

public:
    default_objectmanager();

private Q_SLOTS:
    void testCase1();
};

default_objectmanager::default_objectmanager()
{
}

void default_objectmanager::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(default_objectmanager)

#include "tst_default_objectmanager.moc"
