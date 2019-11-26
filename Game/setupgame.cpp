#include "setupgame.h"

void setupGame(MapWindow *mapWindow,
               std::vector<std::__cxx11::string> playerNames,
               Course::ResourceMap startingResources,
               std::shared_ptr<ObjectManager> objMan)
{
    std::shared_ptr<GameEventHandler> GEHand = mapWindow->getGEHandler();

    // Generate tiles and draw them
    auto& worldGen = Course::WorldGenerator::getInstance();
    worldGen.addConstructor<Course::Forest>(6);
    worldGen.addConstructor<Course::Grassland>(10);
    worldGen.addConstructor<Blockfield>(6);
    worldGen.addConstructor<Water>(10);
    worldGen.addConstructor<OreDeposit>(3);
    unsigned int x = 10;
    unsigned int y = 10;
    unsigned int seed = rand();
    worldGen.generateMap(x, y, seed, objMan, GEHand);
    std::vector<std::shared_ptr<Course::TileBase>> allTiles = objMan->getTiles();
    for(std::shared_ptr<Course::TileBase>& tile: allTiles){
        tile->setDescription("type", "tile");
        mapWindow->drawItem(tile, 0);
    }

    // Generate players and save them
    std::shared_ptr<Player> player1Ptr = std::make_shared<Player>(
                playerNames[0], QString("red"));
    std::shared_ptr<Player> player2Ptr = std::make_shared<Player>(
                playerNames[1], QString("blue"));
    objMan->addPlayer(player1Ptr);
    objMan->addPlayer(player2Ptr);

    GEHand->modifyResources(player1Ptr, startingResources);
    GEHand->modifyResources(player2Ptr, startingResources);

    GEHand->setPlayerInTurn(player1Ptr);
}
