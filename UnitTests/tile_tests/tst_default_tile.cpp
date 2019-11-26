#include <QString>
#include <QtTest>

#include "player.h"
#include "tiles/tilebase.h"
#include "tiles/blockfield.h"
#include "tiles/forest.h"
#include "tiles/grassland.h"
#include "tiles/oredeposit.h"
#include "tiles/water.h"
#include "exceptions/illegalaction.h"
#include "core/coordinate.h"

class default_tile : public QObject
{
    Q_OBJECT

public:
    default_tile();

private Q_SLOTS:
    void test_addBuilding();
    void test_addBuilding_too_many_buildings();
    void test_addBuilding_to_water();
    void test_removeBuilding();

    void cleanup();

private:
    std::shared_ptr<Player> player1;
    std::shared_ptr<Player> player2;

    std::shared_ptr<Course::BuildingBase> building1;
    std::shared_ptr<Course::BuildingBase> building2;

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
    player1 = std::make_shared<Player>("player1", QString("red"));
    player2 = std::make_shared<Player>("player2", QString("blue"));

    building1 = std::make_shared<Course::BuildingBase>(
                nullptr, nullptr, nullptr, 0);
    building2 = std::make_shared<Course::BuildingBase>(
                nullptr, nullptr, nullptr, 0);

    default_object = std::make_shared<Course::TileBase>(coord1, nullptr, nullptr, 1, 1);
    forest_object = std::make_shared<Course::Forest>(coord2, nullptr, nullptr);
    grassland_object = std::make_shared<Course::Grassland>(coord3, nullptr, nullptr);
    blockfield_object = std::make_shared<Blockfield>(coord4, nullptr, nullptr);
    oredeposit_object = std::make_shared<OreDeposit>(coord5, nullptr, nullptr);
    water_object = std::make_shared<Water>(coord6, nullptr, nullptr);
}

void default_tile::test_addBuilding()
{
    // doesnt work because the objecthandler is a nullptr?
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
    building1->setOwner(player1);
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
    QVERIFY_EXCEPTION_THROWN(default_object->addBuilding(building2),
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

void default_tile::cleanup()
{
    player1 = std::make_shared<Player>("player1", QString("red"));
    player2 = std::make_shared<Player>("player2", QString("blue"));
    default_object = std::make_shared<Course::TileBase>(coord1, nullptr, nullptr);
    forest_object = std::make_shared<Course::Forest>(coord2, nullptr, nullptr);
    grassland_object = std::make_shared<Course::Grassland>(coord3, nullptr, nullptr);
    blockfield_object = std::make_shared<Blockfield>(coord4, nullptr, nullptr);
    oredeposit_object = std::make_shared<OreDeposit>(coord5, nullptr, nullptr);
    water_object = std::make_shared<Water>(coord6, nullptr, nullptr);
}


QTEST_APPLESS_MAIN(default_tile)

#include "tst_default_tile.moc"
