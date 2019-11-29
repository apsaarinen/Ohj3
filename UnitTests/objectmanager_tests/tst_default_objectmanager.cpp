#include <QString>
#include <QtTest>

#include "core/gameeventhandler.h"
#include "core/objectmanager.h"
#include "core/player.h"
#include "buildings/buildingbase.h"
#include "workers/basicworker.h"

using namespace Game;

/**
 * @brief The objectmanager_tests test the ObjectManager class
 */
class default_objectmanager : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Test setup
     */
    default_objectmanager();

private Q_SLOTS:

    /**
     * @brief Tests opeations to the list of players
     * @post players should be added and returned correctly
     */
    void test_player_operations();

    /**
     * @brief Tests opeations to the list of tiles
     * @post tiles should be added and returned correctly
     */
    void test_tile_operations();

    /**
     * @brief Tests opeations to the list of placeableobjects \n
     * (workers and buildings)
     * @post placeableobjects should be added and returned correctly
     */
    void test_placeableobject_operations();


    /**
     * @brief Test cleanup
     */
    void cleanup();
private:
    std::shared_ptr<ObjectManager> objectmanager_object;
    std::shared_ptr<GameEventHandler> GEHand;

    int winResourceSum;
    Course::ResourceMap zeroResources;
    Course::ResourceMap startResources;
    Course::ResourceMap minusStartResources;

    std::shared_ptr<Player> player1;
    std::shared_ptr<Player> player2;
    std::shared_ptr<Course::TileBase> tile1;
    std::shared_ptr<Course::TileBase> tile2;

    const Course::Coordinate tile1_coordinate = {1,1};
    const Course::Coordinate tile2_coordinate = {1,2};

    std::shared_ptr<Course::BuildingBase> building1;
    std::shared_ptr<Course::BuildingBase> building2;

    std::shared_ptr<Course::BasicWorker> worker1;
    std::shared_ptr<Course::BasicWorker> worker2;
};

default_objectmanager::default_objectmanager()
{
    objectmanager_object = std::make_shared<ObjectManager>();
    GEHand = std::make_shared<GameEventHandler>();

    player1 = std::make_shared<Player>("player1", QString("red"));
    player2 = std::make_shared<Player>("player2", QString("blue"));

    tile1 = std::make_shared<Course::TileBase>(tile1_coordinate, GEHand, objectmanager_object);
    tile2 = std::make_shared<Course::TileBase>(tile2_coordinate, GEHand, objectmanager_object);

    building1 = std::make_shared<Course::BuildingBase>(
                GEHand, objectmanager_object, nullptr, 1);
    building2 = std::make_shared<Course::BuildingBase>(
                GEHand, objectmanager_object, nullptr, 1);

    worker1 = std::make_shared<Course::BasicWorker>(
                GEHand, objectmanager_object, nullptr, 1);
    worker2 = std::make_shared<Course::BasicWorker>(
                GEHand, objectmanager_object, nullptr, 1);

}

void default_objectmanager::test_player_operations()
{
    QVERIFY(objectmanager_object->getPlayers().size() == 0);
    objectmanager_object->addPlayer(player1);
    QVERIFY(objectmanager_object->getPlayers().at(0) == player1);
    QVERIFY(objectmanager_object->getPlayers().size() == 1);
    objectmanager_object->addPlayer(player2);
    QVERIFY(objectmanager_object->getPlayers().at(0) == player1);
    QVERIFY(objectmanager_object->getPlayers().at(1) == player2);
    QVERIFY(objectmanager_object->getPlayers().size() == 2);
}

void default_objectmanager::test_tile_operations()
{
    QVERIFY(objectmanager_object->getTiles().size() == 0);

    std::vector<std::shared_ptr<Course::TileBase>> tiles;
    tiles.push_back(tile1);
    tiles.push_back(tile2);
    objectmanager_object->addTiles(tiles);
    QVERIFY(objectmanager_object->getTiles().size() == 2);

    QVERIFY(objectmanager_object->getTile(tile1_coordinate) == tile1);

    unsigned int tile1_id = tile1->ID;
    unsigned int tile2_id = tile2->ID;
    QVERIFY(objectmanager_object->getTile(tile1_id) == tile1);
    QVERIFY(objectmanager_object->getTile(tile2_id) == tile2);

    std::vector<Course::Coordinate> coordinates;
    coordinates.push_back(tile1_coordinate);
    coordinates.push_back(tile2_coordinate);
    QVERIFY(objectmanager_object->getTiles(coordinates).at(0) == tile1);
    QVERIFY(objectmanager_object->getTiles(coordinates).at(1) == tile2);
}

void default_objectmanager::test_placeableobject_operations()
{
    QVERIFY(objectmanager_object->getNewestPlaceableObject() == nullptr);
    objectmanager_object->addPlaceableObject(building1);
    QVERIFY(objectmanager_object->getNewestPlaceableObject() == building1);
    objectmanager_object->addPlaceableObject(worker1);
    QVERIFY(objectmanager_object->getNewestPlaceableObject() == worker1);
}

void default_objectmanager::cleanup()
{
    objectmanager_object = std::make_shared<ObjectManager>();
    GEHand = std::make_shared<GameEventHandler>();

    player1 = std::make_shared<Player>("player1", QString("red"));
    player2 = std::make_shared<Player>("player2", QString("blue"));

    tile1 = std::make_shared<Course::TileBase>(tile1_coordinate, GEHand, objectmanager_object);
    tile2 = std::make_shared<Course::TileBase>(tile2_coordinate, GEHand, objectmanager_object);

    building1 = std::make_shared<Course::BuildingBase>(
                GEHand, objectmanager_object, nullptr, 1);
    building2 = std::make_shared<Course::BuildingBase>(
                GEHand, objectmanager_object, nullptr, 1);

    worker1 = std::make_shared<Course::BasicWorker>(
                GEHand, objectmanager_object, nullptr, 1);
    worker2 = std::make_shared<Course::BasicWorker>(
                GEHand, objectmanager_object, nullptr, 1);
}


QTEST_APPLESS_MAIN(default_objectmanager)

#include "tst_default_objectmanager.moc"
