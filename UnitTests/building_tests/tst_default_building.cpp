#include <QString>
#include <QtTest>

#include "core/player.h"
#include "buildings/buildingbase.h"
#include "buildings/farm.h"
#include "buildings/outpost.h"
#include "buildings/headquarters.h"
#include "buildings/mine.hh"
#include "buildings/sawmill.hh"
#include "tiles/tilebase.h"
#include "exceptions/illegalaction.h"
#include "core/coordinate.h"
#include "core/objectmanager.h"
#include "core/gameeventhandler.h"

using namespace Game;

/**
 * @brief The building_tests test the PlaceableGameObject and all Building classes
 */
class default_building : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Test setup
     */
    default_building();

private Q_SLOTS:

    // Tests as a PlaceableGameObject

    /**
     * @brief Tests whether an object with the same owner \n
     *  can be placed on a tile
     * @post Should be possible
     */
    void test_canBePlacedOnTile_same_owner();

    /**
     * @brief Tests whether an object with a different owner \n
     *  can be placed on a tile
     * @post Should not be possible
     */
    void test_canBePlacedOnTile_ownerconflict();

    /**
     * @brief Tests whether an owned object \n
     *  can be placed on a tile with no owner
     * @post Should be possible
     */
    void test_canBePlacedOnTile_no_owner_for_tile();

    /**
     * @brief Tests whether an object with no owner \n
     *  can be placed on a tile with an owner
     * @post Should be possible
     */
    void test_canBePlacedOnTile_no_owner_for_object();

    /**
     * @brief Tests whether an object with no owner \n
     *  can be placed on a tile without an owner
     * @post Should be possible
     */
    void test_canBePlacedOnTile_no_owners();

    /**
     * @brief Tests whether an object can be placed on a tile
     * @post Should be possible
     */
    void test_setLocationTile();

    /**
     * @brief Tests whether an object's location can be removed
     * @post Should be possible
     */
    void test_unsetLocationTile();

    /**
     * @brief Tests whether an object's location can set to a tile \n
     * with a different owner
     * @post Should throw an IllegalAction exception
     */
    void test_setLocationTile_exception();

    /**
     * @brief Tests whether an objects location gets removed if the \n
     * tile expires it was located on
     * @post Should be removed
     */
    void test_currentLocationTile_expired_ptr();


    // Tests as a BuildingBase

    /**
     * @brief Tests if an HQ buildings onbuildaction works
     * @post Should work
     */
    void test_onBuildAction();

    /**
     * @brief Tests adding a hold marker to a building
     * @post Should be possible
     */
    void test_addHoldMarkers();

    /**
     * @brief Tests BuildingBase's type
     * @post Should be BuildingBase
     */
    void test_type_BuildingBase();

    /**
     * @brief Tests HeadQuarter's type
     * @post Should be HeadQuarters
     */
    void test_type_HQ();

    /**
     * @brief Tests Outpost's type
     * @post Should be Outpost
     */
    void test_type_Outpost();

    /**
     * @brief Tests Farm's type
     * @post Should be Farm
     */
    void test_type_Farm();

    /**
     * @brief Tests Sawmill's type
     * @post Should be Sawmill
     */
    void test_type_SawMill();

    /**
     * @brief Tests Mine's type
     * @post Should be Mine
     */
    void test_type_Mine();


    /**
     * @brief Test cleanup
     */
    void cleanup();

private:
    std::shared_ptr<ObjectManager> objMan;
    std::shared_ptr<GameEventHandler> GEHand;

    std::shared_ptr<Player> player1;
    std::shared_ptr<Player> player2;
    std::shared_ptr<Course::TileBase> tile1;
    std::shared_ptr<Course::TileBase> tile2;
    std::shared_ptr<Course::TileBase> tileExpire;

    const Course::Coordinate tile1_coordinate = {1,1};
    const Course::Coordinate tile2_coordinate = {1,2};
    const Course::Coordinate tileExpire_coordinate = {2,2};

    std::shared_ptr<Course::BuildingBase> default_object;
    std::shared_ptr<Course::HeadQuarters> hq_object;
    std::shared_ptr<Course::Outpost> outpost_object;
    std::shared_ptr<Course::Farm> farm_object;
    std::shared_ptr<Mine> mine_object;
    std::shared_ptr<SawMill> sawmill_object;

};

default_building::default_building()
{
    objMan = std::make_shared<ObjectManager>();
    GEHand = std::make_shared<GameEventHandler>();

    player1 = std::make_shared<Player>("player1", QString("red"));
    player2 = std::make_shared<Player>("player2", QString("blue"));
    objMan->addPlayer(player1);
    objMan->addPlayer(player2);

    tile1 = std::make_shared<Course::TileBase>(tile1_coordinate, GEHand, objMan);
    tile2 = std::make_shared<Course::TileBase>(tile2_coordinate, GEHand, objMan);
    std::vector<std::shared_ptr<Course::TileBase>> tiles;
    tiles.push_back(tile1);
    tiles.push_back(tile2);
    objMan->addTiles(tiles);
    // We don't want to add this tile to the ObjectManager
    tileExpire = std::make_shared<Course::TileBase>(tileExpire_coordinate, GEHand, objMan);

    default_object = std::make_shared<Course::BuildingBase>(
                GEHand, objMan, nullptr, 1);
    hq_object = std::make_shared<Course::HeadQuarters>(
                GEHand, objMan, nullptr);
    outpost_object = std::make_shared<Course::Outpost>(
                GEHand, objMan, nullptr);
    farm_object = std::make_shared<Course::Farm>(
                GEHand, objMan, nullptr);
    mine_object = std::make_shared<Mine>(
                GEHand, objMan, nullptr);
    sawmill_object = std::make_shared<SawMill>(
                GEHand, objMan, nullptr);
    objMan->addPlaceableObject(default_object);
    objMan->addPlaceableObject(hq_object);
    objMan->addPlaceableObject(outpost_object);
    objMan->addPlaceableObject(farm_object);
    objMan->addPlaceableObject(mine_object);
    objMan->addPlaceableObject(sawmill_object);
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

void default_building::test_currentLocationTile_expired_ptr()
{
    QVERIFY(default_object->currentLocationTile() == nullptr);
    default_object->setLocationTile(tileExpire);
    QVERIFY(default_object->currentLocationTile() == tileExpire);
    tileExpire = {};
    QVERIFY(default_object->currentLocationTile() == nullptr);
}

void default_building::test_onBuildAction()
{
    hq_object->setOwner(player1);
    default_object->setOwner(player2);
    tile1->setOwner(player1);
    hq_object->setLocationTile(tile1);
    hq_object->onBuildAction();
    QVERIFY(!default_object->canBePlacedOnTile(tile2));
}

void default_building::test_addHoldMarkers()
{
    default_object->addHoldMarkers(1);
    QVERIFY(default_object->holdCount() == 1);
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
    objMan = std::make_shared<ObjectManager>();
    GEHand = std::make_shared<GameEventHandler>();

    player1 = std::make_shared<Player>("player1", QString("red"));
    player2 = std::make_shared<Player>("player2", QString("blue"));
    objMan->addPlayer(player1);
    objMan->addPlayer(player2);

    tile1 = std::make_shared<Course::TileBase>(tile1_coordinate, GEHand, objMan);
    tile2 = std::make_shared<Course::TileBase>(tile2_coordinate, GEHand, objMan);
    std::vector<std::shared_ptr<Course::TileBase>> tiles;
    tiles.push_back(tile1);
    tiles.push_back(tile2);
    objMan->addTiles(tiles);
    // We don't want to add this tile to the ObjectManager
    tileExpire = std::make_shared<Course::TileBase>(tileExpire_coordinate, GEHand, objMan);

    default_object = std::make_shared<Course::BuildingBase>(
                GEHand, objMan, nullptr, 1);
    hq_object = std::make_shared<Course::HeadQuarters>(
                GEHand, objMan, nullptr);
    outpost_object = std::make_shared<Course::Outpost>(
                GEHand, objMan, nullptr);
    farm_object = std::make_shared<Course::Farm>(
                GEHand, objMan, nullptr);
    mine_object = std::make_shared<Mine>(
                GEHand, objMan, nullptr);
    sawmill_object = std::make_shared<SawMill>(
                GEHand, objMan, nullptr);
    objMan->addPlaceableObject(default_object);
    objMan->addPlaceableObject(hq_object);
    objMan->addPlaceableObject(outpost_object);
    objMan->addPlaceableObject(farm_object);
    objMan->addPlaceableObject(mine_object);
    objMan->addPlaceableObject(sawmill_object);
}

QTEST_APPLESS_MAIN(default_building)

#include "tst_default_building.moc"
