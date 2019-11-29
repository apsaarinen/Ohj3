#include <QString>
#include <QtTest>

#include "core/player.h"
#include "buildings/buildingbase.h"
#include "workers/workerbase.h"
#include "workers/basicworker.h"
#include "tiles/tilebase.h"
#include "tiles/blockfield.h"
#include "tiles/forest.h"
#include "tiles/grassland.h"
#include "tiles/oredeposit.h"
#include "tiles/water.h"
#include "exceptions/illegalaction.h"
#include "core/coordinate.h"
#include "core/objectmanager.h"
#include "core/gameeventhandler.h"

using namespace Game;

/**
 * @brief The tiles_tests test the TileBase class and all its children
 */
class default_tile : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Test setup
     */
    default_tile();

private Q_SLOTS:

    /**
     * @brief Tests adding a building to a tile
     * @post Should be possible
     */
    void test_addBuilding();

    /**
     * @brief Tests adding too many buildings on a tile
     * @post Should throw an IllegalAction exception
     */
    void test_addBuilding_too_many_buildings();

    /**
     * @brief Tests adding a building to water
     * @post Should throw an IllegalAction exception
     */
    void test_addBuilding_to_water();

    /**
     * @brief Tests removing a building from a tile
     * @post Should be possible
     */
    void test_removeBuilding();

    /**
     * @brief Tests getting buildings from a tile
     * @post Should be possible
     */
    void test_getBuildings();

    /**
     * @brief Tests adding a worker to a tile
     * @post Should be possible
     */
    void test_addWorker();

    /**
     * @brief Tests adding too many workers on a tile
     * @post Should throw an IllegalAction exception
     */
    void test_addWorker_too_many_workers();

    /**
     * @brief Tests adding a worker to water
     * @post Should throw an IllegalAction exception
     */
    void test_addWorker_to_water();

    /**
     * @brief Tests removing a worker from a tile
     * @post Should be possible
     */
    void test_removeWorker();

    /**
     * @brief Tests getting workers from a tile
     * @post Should be possible
     */
    void test_getWorkers();

    /**
     * @brief Tests adding workers and buildings to a tile
     * @post Should be possible to add both within limits of the tile
     */
    void test_addBuildingAndWorker();

    /**
     * @brief Tests TilesBase's type
     * @post Should be TilesBase
     */
    void test_type_tilebase();

    /**
     * @brief Tests Forest's type
     * @post Should be Forest
     */
    void test_type_forest();

    /**
     * @brief Tests Grassland's type
     * @post Should be Grassland
     */
    void test_type_grassland();

    /**
     * @brief Tests Water's type
     * @post Should be Water
     */
    void test_type_water();

    /**
     * @brief Tests Blockfield's type
     * @post Should be Blockfield
     */
    void test_type_blockfield();

    /**
     * @brief Tests OreDeposit's type
     * @post Should be OreDeposit
     */
    void test_type_oredeposit();


    /**
     * @brief Test cleanup
     */
    void cleanup();

private:
    std::shared_ptr<ObjectManager> objMan;
    std::shared_ptr<GameEventHandler> GEHand;

    std::shared_ptr<Player> player1;
    std::shared_ptr<Player> player2;

    std::shared_ptr<Course::BuildingBase> building1;
    std::shared_ptr<Course::BuildingBase> building2;

    std::shared_ptr<Course::BasicWorker> worker1;
    std::shared_ptr<Course::BasicWorker> worker2;

    std::shared_ptr<Course::TileBase> default_object;
    std::shared_ptr<Course::Forest> forest_object;
    std::shared_ptr<Course::Grassland> grassland_object;
    std::shared_ptr<Blockfield> blockfield_object;
    std::shared_ptr<OreDeposit> oredeposit_object;
    std::shared_ptr<Water> water_object;

    const Course::Coordinate coord1 = {1,1};
    const Course::Coordinate coord2 = {2,2};
    const Course::Coordinate coord3 = {3,3};
    const Course::Coordinate coord4 = {4,4};
    const Course::Coordinate coord5 = {5,5};
    const Course::Coordinate coord6 = {6,6};

};

default_tile::default_tile()
{
    objMan = std::make_shared<ObjectManager>();
    GEHand = std::make_shared<GameEventHandler>();

    player1 = std::make_shared<Player>("player1", QString("red"));
    player2 = std::make_shared<Player>("player2", QString("blue"));
    objMan->addPlayer(player1);
    objMan->addPlayer(player2);

    building1 = std::make_shared<Course::BuildingBase>(
                GEHand, objMan, nullptr, 1);
    building2 = std::make_shared<Course::BuildingBase>(
                GEHand, objMan, nullptr, 1);
    objMan->addPlaceableObject(building1);
    objMan->addPlaceableObject(building2);

    worker1 = std::make_shared<Course::BasicWorker>(
              GEHand, objMan, nullptr, 1);
    worker2 = std::make_shared<Course::BasicWorker>(
              GEHand, objMan, nullptr, 1);
    objMan->addPlaceableObject(worker1);
    objMan->addPlaceableObject(worker2);

    default_object = std::make_shared<Course::TileBase>(coord1, GEHand, objMan, 1, 1);
    forest_object = std::make_shared<Course::Forest>(coord2, GEHand, objMan);
    grassland_object = std::make_shared<Course::Grassland>(coord3, GEHand, objMan);
    blockfield_object = std::make_shared<Blockfield>(coord4, GEHand, objMan);
    oredeposit_object = std::make_shared<OreDeposit>(coord5, GEHand, objMan);
    water_object = std::make_shared<Water>(coord6, GEHand, objMan);
    std::vector<std::shared_ptr<Course::TileBase>> tiles;
    tiles.push_back(default_object);
    tiles.push_back(forest_object);
    tiles.push_back(grassland_object);
    tiles.push_back(blockfield_object);
    tiles.push_back(oredeposit_object);
    tiles.push_back(water_object);
    objMan->addTiles(tiles);
}

void default_tile::test_addBuilding()
{
    default_object->setOwner(player1);
    building1->setOwner(player1);
    QVERIFY(default_object->getBuildingCount() == 0);
    default_object->addBuilding(building1);
    QVERIFY(default_object->getBuildingCount() == 1);
}

void default_tile::test_addBuilding_too_many_buildings()
{
    default_object->setOwner(player1);
    building1->setOwner(player1);
    building2->setOwner(player1);
    QVERIFY(default_object->getBuildingCount() == 0);
    default_object->addBuilding(building1);
    QVERIFY_EXCEPTION_THROWN(default_object->addBuilding(building2),
                             Course::IllegalAction);
}

void default_tile::test_addBuilding_to_water()
{
    water_object->setOwner(player1);
    building1->setOwner(player1);
    QVERIFY(default_object->getBuildingCount() == 0);
    QVERIFY_EXCEPTION_THROWN(water_object->addBuilding(building1),
                             Course::IllegalAction);
}


void default_tile::test_removeBuilding()
{
    default_object->setOwner(player1);
    building1->setOwner(player1);
    QVERIFY(default_object->getBuildingCount() == 0);
    default_object->addBuilding(building1);
    QVERIFY(default_object->getBuildingCount() == 1);
    default_object->removeBuilding(building1);
    QVERIFY(default_object->getBuildingCount() == 0);
}

void default_tile::test_getBuildings()
{
    default_object->setOwner(player1);
    building1->setOwner(player1);
    QVERIFY(default_object->getBuildingCount() == 0);
    default_object->addBuilding(building1);
    QVERIFY(default_object->getBuildings().at(0) == building1);
}

void default_tile::test_addWorker()
{
    default_object->setOwner(player1);
    worker1->setOwner(player1);
    QVERIFY(default_object->getWorkerCount() == 0);
    default_object->addWorker(worker1);
    QVERIFY(default_object->getWorkerCount() == 1);
}

void default_tile::test_addWorker_too_many_workers()
{
    default_object->setOwner(player1);
    worker1->setOwner(player1);
    worker2->setOwner(player1);
    QVERIFY(default_object->getWorkerCount() == 0);
    default_object->addWorker(worker1);
    QVERIFY_EXCEPTION_THROWN(default_object->addWorker(worker2),
                             Course::IllegalAction);
}

void default_tile::test_addWorker_to_water()
{
    water_object->setOwner(player1);
    worker1->setOwner(player1);
    QVERIFY(default_object->getWorkerCount() == 0);
    QVERIFY_EXCEPTION_THROWN(water_object->addWorker(worker1),
                             Course::IllegalAction);
}

void default_tile::test_removeWorker()
{
    default_object->setOwner(player1);
    worker1->setOwner(player1);
    QVERIFY(default_object->getWorkerCount() == 0);
    default_object->addWorker(worker1);
    QVERIFY(default_object->getWorkerCount() == 1);
    default_object->removeWorker(worker1);
    QVERIFY(default_object->getWorkerCount() == 0);
}

void default_tile::test_getWorkers()
{
    default_object->setOwner(player1);
    worker1->setOwner(player1);
    QVERIFY(default_object->getWorkerCount() == 0);
    default_object->addWorker(worker1);
    QVERIFY(default_object->getWorkers().at(0) == worker1);
}

void default_tile::test_addBuildingAndWorker()
{
    default_object->setOwner(player1);
    building1->setOwner(player1);
    building2->setOwner(player1);
    QVERIFY(default_object->getBuildingCount() == 0);
    default_object->addBuilding(building1);
    QVERIFY_EXCEPTION_THROWN(default_object->addBuilding(building2),
                             Course::IllegalAction);

    default_object->setOwner(player1);
    worker1->setOwner(player1);
    worker2->setOwner(player1);
    QVERIFY(default_object->getWorkerCount() == 0);
    default_object->addWorker(worker1);
    QVERIFY_EXCEPTION_THROWN(default_object->addWorker(worker2),
                             Course::IllegalAction);
}

void default_tile::test_type_tilebase()
{
    QVERIFY(default_object->getType() == "TileBase");
}

void default_tile::test_type_forest()
{
    QVERIFY(forest_object->getType() == "Forest");
}

void default_tile::test_type_grassland()
{
    QVERIFY(grassland_object->getType() == "Grassland");
}

void default_tile::test_type_water()
{
    QVERIFY(water_object->getType() == "Water");
}

void default_tile::test_type_blockfield()
{
    QVERIFY(blockfield_object->getType() == "Blockfield");
}

void default_tile::test_type_oredeposit()
{
    QVERIFY(oredeposit_object->getType() == "OreDeposit");
}

void default_tile::cleanup()
{
    objMan = std::make_shared<ObjectManager>();
    GEHand = std::make_shared<GameEventHandler>();

    player1 = std::make_shared<Player>("player1", QString("red"));
    player2 = std::make_shared<Player>("player2", QString("blue"));
    objMan->addPlayer(player1);
    objMan->addPlayer(player2);

    building1 = std::make_shared<Course::BuildingBase>(
                GEHand, objMan, nullptr, 1);
    building2 = std::make_shared<Course::BuildingBase>(
                GEHand, objMan, nullptr, 1);
    objMan->addPlaceableObject(building1);
    objMan->addPlaceableObject(building2);

    worker1 = std::make_shared<Course::BasicWorker>(
              GEHand, objMan, nullptr, 1);
    worker2 = std::make_shared<Course::BasicWorker>(
              GEHand, objMan, nullptr, 1);
    objMan->addPlaceableObject(worker1);
    objMan->addPlaceableObject(worker2);

    default_object = std::make_shared<Course::TileBase>(coord1, GEHand, objMan, 1, 1);
    forest_object = std::make_shared<Course::Forest>(coord2, GEHand, objMan);
    grassland_object = std::make_shared<Course::Grassland>(coord3, GEHand, objMan);
    blockfield_object = std::make_shared<Blockfield>(coord4, GEHand, objMan);
    oredeposit_object = std::make_shared<OreDeposit>(coord5, GEHand, objMan);
    water_object = std::make_shared<Water>(coord6, GEHand, objMan);
    std::vector<std::shared_ptr<Course::TileBase>> tiles;
    tiles.push_back(default_object);
    tiles.push_back(forest_object);
    tiles.push_back(grassland_object);
    tiles.push_back(blockfield_object);
    tiles.push_back(oredeposit_object);
    tiles.push_back(water_object);
    objMan->addTiles(tiles);
}


QTEST_APPLESS_MAIN(default_tile)

#include "tst_default_tile.moc"
