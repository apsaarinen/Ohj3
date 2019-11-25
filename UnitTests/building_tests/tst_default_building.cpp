#include <QString>
#include <QtTest>

#include "player.h"
#include "buildings/buildingbase.h"
#include "buildings/farm.h"
#include "buildings/outpost.h"
#include "buildings/headquarters.h"
#include "buildings/mine.hh"
#include "buildings/sawmill.hh"
#include "tiles/tilebase.h"
#include "exceptions/illegalaction.h"
#include "core/coordinate.h"

class default_building : public QObject
{
    Q_OBJECT

public:
    default_building();

private Q_SLOTS:
    void test_canBePlacedOnTile_same_owner();
    void test_canBePlacedOnTile_ownerconflict();
    void test_canBePlacedOnTile_no_owner_for_tile();
    void test_canBePlacedOnTile_no_owner_for_object();
    void test_canBePlacedOnTile_no_owners();

    void test_setLocationTile();
    void test_unsetLocationTile();
    void test_setLocationTile_exception();

    void test_addHoldMarkers();

    void test_currentLocationTile_expired_ptr();

    void test_type_BuildingBase();
    void test_type_HQ();
    void test_type_Outpost();
    void test_type_Farm();
    void test_type_SawMill();
    void test_type_Mine();

    void cleanup();

private:
    std::shared_ptr<Player> player1;
    std::shared_ptr<Player> player2;
    std::shared_ptr<Course::TileBase> tile1;
    std::shared_ptr<Course::TileBase> tile2;

    const Course::Coordinate tile1_coordinate = {1,1};
    const Course::Coordinate tile2_coordinate = {1,2};

    std::shared_ptr<Course::BuildingBase> default_object;
    std::shared_ptr<Course::HeadQuarters> hq_object;
    std::shared_ptr<Course::Outpost> outpost_object;
    std::shared_ptr<Course::Farm> farm_object;
    std::shared_ptr<Mine> mine_object;
    std::shared_ptr<SawMill> sawmill_object;

};

default_building::default_building()
{
    player1 = std::make_shared<Player>("player1", QString("red"));
    player2 = std::make_shared<Player>("player2", QString("blue"));
    tile1 = std::make_shared<Course::TileBase>(tile1_coordinate, nullptr, nullptr);
    tile2 = std::make_shared<Course::TileBase>(tile2_coordinate, nullptr, nullptr);
    default_object = std::make_shared<Course::BuildingBase>(
                nullptr, nullptr, nullptr, 2);
    hq_object = std::make_shared<Course::HeadQuarters>(
                nullptr, nullptr, nullptr);
    outpost_object = std::make_shared<Course::Outpost>(
                nullptr, nullptr, nullptr);
    farm_object = std::make_shared<Course::Farm>(
                nullptr, nullptr, nullptr);
    mine_object = std::make_shared<Mine>(
                nullptr, nullptr, nullptr);
    sawmill_object = std::make_shared<SawMill>(
                nullptr, nullptr, nullptr);
}

void default_building::test_canBePlacedOnTile_same_owner()
{
    tile1->setOwner(player1);
    default_object->setOwner(player1);

    QVERIFY(default_object->getOwner() == player1);
    QVERIFY(tile1->getOwner() == player1);
    QVERIFY(default_object->canBePlacedOnTile(tile1));
}

void default_building::test_canBePlacedOnTile_ownerconflict()
{
    tile1->setOwner(player1);
    default_object->setOwner(player2);

    QVERIFY(default_object->getOwner() == player2);
    QVERIFY(tile1->getOwner() == player1);
    QVERIFY(not default_object->canBePlacedOnTile(tile1));
}

void default_building::test_canBePlacedOnTile_no_owner_for_tile()
{
    default_object->setOwner(player1);

    QVERIFY(default_object->getOwner() == player1);
    QVERIFY(tile1->getOwner() == nullptr);
    QVERIFY(default_object->canBePlacedOnTile(tile1));
}

void default_building::test_canBePlacedOnTile_no_owner_for_object()
{
    tile1->setOwner(player1);

    QVERIFY(default_object->getOwner() == nullptr);
    QVERIFY(tile1->getOwner() == player1);
    QVERIFY(default_object->canBePlacedOnTile(tile1));
}

void default_building::test_canBePlacedOnTile_no_owners()
{
    QVERIFY(default_object->getOwner() == nullptr);
    QVERIFY(tile1->getOwner() == nullptr);
    QVERIFY(default_object->canBePlacedOnTile(tile1));
}

void default_building::test_setLocationTile()
{
    QVERIFY(default_object->currentLocationTile() == nullptr);
    default_object->setLocationTile(tile1);
    QVERIFY(default_object->currentLocationTile() == tile1);
}

void default_building::test_unsetLocationTile()
{
    QVERIFY(default_object->currentLocationTile() == nullptr);
    default_object->setLocationTile(tile1);
    QVERIFY(default_object->currentLocationTile() == tile1);
    default_object->setLocationTile(nullptr);
    QVERIFY(default_object->currentLocationTile() == nullptr);
}

void default_building::test_setLocationTile_exception()
{
    default_object->setOwner(player1);
    tile1->setOwner(player2);

    QVERIFY(not default_object->canBePlacedOnTile(tile1));
    QVERIFY_EXCEPTION_THROWN(default_object->setLocationTile(tile1),
                             Course::IllegalAction);
}

void default_building::test_addHoldMarkers()
{
    default_object->addHoldMarkers(1);
    QVERIFY(default_object->holdCount() == 1);
}

void default_building::test_currentLocationTile_expired_ptr()
{
    QVERIFY(default_object->currentLocationTile() == nullptr);
    default_object->setLocationTile(tile1);
    QVERIFY(default_object->currentLocationTile() == tile1);
    tile1 = {};
    QVERIFY(default_object->currentLocationTile() == nullptr);
}

void default_building::test_type_BuildingBase()
{
    QVERIFY(default_object->getType() == "BuildingBase");
}

void default_building::test_type_HQ()
{
    QVERIFY(hq_object->getType() == "HeadQuarters");
}

void default_building::test_type_Outpost()
{
    QVERIFY(outpost_object->getType() == "Outpost");
}

void default_building::test_type_Farm()
{
    QVERIFY(farm_object->getType() == "Farm");
}

void default_building::test_type_SawMill()
{
    QVERIFY(sawmill_object->getType() == "Sawmill");
}

void default_building::test_type_Mine()
{
    QVERIFY(mine_object->getType() == "Mine");
}

void default_building::cleanup()
{
    player1 = std::make_shared<Player>("player1", QString("red"));
    player2 = std::make_shared<Player>("player2", QString("blue"));
    tile1 = std::make_shared<Course::TileBase>(tile1_coordinate, nullptr, nullptr);
    tile2 = std::make_shared<Course::TileBase>(tile2_coordinate, nullptr, nullptr);
    default_object = std::make_shared<Course::BuildingBase>(
                nullptr, nullptr, nullptr, 2);
    hq_object = std::make_shared<Course::HeadQuarters>(
                nullptr, nullptr, nullptr);
    outpost_object = std::make_shared<Course::Outpost>(
                nullptr, nullptr, nullptr);
    farm_object = std::make_shared<Course::Farm>(
                nullptr, nullptr, nullptr);
    mine_object = std::make_shared<Mine>(
                nullptr, nullptr, nullptr);
    sawmill_object = std::make_shared<SawMill>(
                nullptr, nullptr, nullptr);
}

QTEST_APPLESS_MAIN(default_building)

#include "tst_default_building.moc"
