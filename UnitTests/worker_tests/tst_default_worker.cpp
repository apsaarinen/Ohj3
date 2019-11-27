#include <QString>
#include <QtTest>

#include "player.h"
#include "workers/workerbase.h"
#include "workers/basicworker.h"
#include "workers/mineworker.h"
#include "workers/sawmillworker.h"
#include "buildings/buildingbase.h"
#include "tiles/tilebase.h"
#include "exceptions/illegalaction.h"
#include "core/coordinate.h"
#include "objectmanager.h"
#include "gameeventhandler.h"
#include "core/basicresources.h"

class default_worker : public QObject
{
    Q_OBJECT

public:
    default_worker();

private Q_SLOTS:
    // Tests as a PlaceableGameObject
    void test_canBePlacedOnTile_same_owner();
    void test_canBePlacedOnTile_ownerconflict();
    void test_canBePlacedOnTile_no_owners();
    void test_setLocationTile();
    void test_unsetLocationTile();
    void test_setLocationTile_exception();
    void test_currentLocationTile_expired_ptr();
    
    // Tests as a BasicWorker
    void test_tileWorkAction();
    void test_tileWorkAction_notEnoughMoneyAndFood();
    void test_type_basicworker();
    void test_type_mineworker();
    void test_type_sawmillworker();

    void cleanup();

private:
    std::shared_ptr<ObjectManager> objMan;
    std::shared_ptr<GameEventHandler> GEHand;

    Course::ResourceMap startResources;

    std::shared_ptr<Player> player1;
    std::shared_ptr<Player> player2;
    std::shared_ptr<Course::TileBase> tile1;
    std::shared_ptr<Course::TileBase> tile2;
    std::shared_ptr<Course::TileBase> tileExpire;

    const Course::Coordinate tile1_coordinate = {1,1};
    const Course::Coordinate tile2_coordinate = {1,2};
    const Course::Coordinate tileExpire_coordinate = {2,2};

    std::shared_ptr<Course::BasicWorker> default_object;
    std::shared_ptr<SawMillWorker> sawmillworker_object;
    std::shared_ptr<MineWorker> mineworker_object;
};

default_worker::default_worker()
{
    objMan = std::make_shared<ObjectManager>();
    GEHand = std::make_shared<GameEventHandler>();

    startResources = {
        {Course::BasicResource::MONEY, 100},
        {Course::BasicResource::FOOD, 100},
        {Course::BasicResource::WOOD, 100},
        {Course::BasicResource::STONE, 100},
        {Course::BasicResource::ORE, 100},
    };
    player1 = std::make_shared<Player>("player1", QString("red"));
    player2 = std::make_shared<Player>("player2", QString("blue"));
    GEHand->modifyResources(player1, startResources);
    GEHand->modifyResources(player2, startResources);
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

    default_object = std::make_shared<Course::BasicWorker>(
                GEHand, objMan, nullptr, 1);
    mineworker_object = std::make_shared<MineWorker>(
                GEHand, objMan, nullptr);
    sawmillworker_object = std::make_shared<SawMillWorker>(
                GEHand, objMan, nullptr);
    objMan->addPlaceableObject(default_object);
    objMan->addPlaceableObject(mineworker_object);
    objMan->addPlaceableObject(sawmillworker_object);
}

void default_worker::test_canBePlacedOnTile_same_owner()
{
    tile1->setOwner(player1);
    default_object->setOwner(player1);

    QVERIFY(default_object->getOwner() == player1);
    QVERIFY(tile1->getOwner() == player1);
    QVERIFY(default_object->canBePlacedOnTile(tile1));
}

void default_worker::test_canBePlacedOnTile_ownerconflict()
{
    tile1->setOwner(player1);
    default_object->setOwner(player2);

    QVERIFY(default_object->getOwner() == player2);
    QVERIFY(tile1->getOwner() == player1);
    QVERIFY(not default_object->canBePlacedOnTile(tile1));
}

void default_worker::test_canBePlacedOnTile_no_owners()
{
    QVERIFY(default_object->getOwner() == nullptr);
    QVERIFY(tile1->getOwner() == nullptr);
    QVERIFY(default_object->canBePlacedOnTile(tile1));
}

void default_worker::test_setLocationTile()
{
    QVERIFY(default_object->currentLocationTile() == nullptr);
    default_object->setLocationTile(tile1);
    QVERIFY(default_object->currentLocationTile() == tile1);
}

void default_worker::test_unsetLocationTile()
{
    QVERIFY(default_object->currentLocationTile() == nullptr);
    default_object->setLocationTile(tile1);
    QVERIFY(default_object->currentLocationTile() == tile1);
    default_object->setLocationTile(nullptr);
    QVERIFY(default_object->currentLocationTile() == nullptr);
}

void default_worker::test_setLocationTile_exception()
{
    default_object->setOwner(player1);
    tile1->setOwner(player2);

    QVERIFY(not default_object->canBePlacedOnTile(tile1));
    QVERIFY_EXCEPTION_THROWN(default_object->setLocationTile(tile1),
                             Course::IllegalAction);
}

void default_worker::test_currentLocationTile_expired_ptr()
{
    QVERIFY(default_object->currentLocationTile() == nullptr);
    default_object->setLocationTile(tileExpire);
    QVERIFY(default_object->currentLocationTile() == tileExpire);
    tileExpire = {};
    QVERIFY(default_object->currentLocationTile() == nullptr);
}

void default_worker::test_tileWorkAction()
{
    default_object->setOwner(player1);
    QVERIFY(player1->getResources().at(Course::BasicResource::MONEY) == 100);
    QVERIFY(player1->getResources().at(Course::BasicResource::FOOD) == 100);
    QVERIFY(default_object->tileWorkAction().at(Course::BasicResource::MONEY) == 0.25);
    QVERIFY(player1->getResources().at(Course::BasicResource::MONEY) == 99);
    QVERIFY(player1->getResources().at(Course::BasicResource::FOOD) == 99);
}

void default_worker::test_tileWorkAction_notEnoughMoneyAndFood()
{
    default_object->setOwner(player1);
    QVERIFY(player1->getResources().at(Course::BasicResource::MONEY) == 100);
    QVERIFY(player1->getResources().at(Course::BasicResource::FOOD) == 100);
    Course::ResourceMap startResourceInverse = Course::multiplyResourceMap(startResources,
                                                           Course::ConstResourceMaps::NEGATIVE);
    GEHand->modifyResources(player1, startResourceInverse);
    Course::ResourceMap asd = player1->getResources();
    QVERIFY(player1->getResources().at(Course::BasicResource::MONEY) == 0);
    QVERIFY(player1->getResources().at(Course::BasicResource::FOOD) == 0);
    QVERIFY(default_object->tileWorkAction().at(Course::BasicResource::MONEY) == 0);
}

void default_worker::test_type_basicworker()
{
    QVERIFY(default_object->getType() == "BasicWorker");
}

void default_worker::test_type_mineworker()
{
    QVERIFY(mineworker_object->getType() == "MineWorker");
}

void default_worker::test_type_sawmillworker()
{
    QVERIFY(sawmillworker_object->getType() == "SawMillWorker");
}

void default_worker::cleanup()
{
    objMan = std::make_shared<ObjectManager>();
    GEHand = std::make_shared<GameEventHandler>();

    startResources = {
        {Course::BasicResource::MONEY, 100},
        {Course::BasicResource::FOOD, 100},
        {Course::BasicResource::WOOD, 100},
        {Course::BasicResource::STONE, 100},
        {Course::BasicResource::ORE, 100},
    };
    player1 = std::make_shared<Player>("player1", QString("red"));
    player2 = std::make_shared<Player>("player2", QString("blue"));
    GEHand->modifyResources(player1, startResources);
    GEHand->modifyResources(player2, startResources);
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

    default_object = std::make_shared<Course::BasicWorker>(
                GEHand, objMan, nullptr, 1);
    mineworker_object = std::make_shared<MineWorker>(
                GEHand, objMan, nullptr);
    sawmillworker_object = std::make_shared<SawMillWorker>(
                GEHand, objMan, nullptr);
    objMan->addPlaceableObject(default_object);
    objMan->addPlaceableObject(mineworker_object);
    objMan->addPlaceableObject(sawmillworker_object);
}

QTEST_APPLESS_MAIN(default_worker)

#include "tst_default_worker.moc"
