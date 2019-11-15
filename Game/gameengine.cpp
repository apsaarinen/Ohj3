#include "gameengine.h"

GameEngine::GameEngine()
{

}

void GameEngine::setupGame(MapWindow *mapWindow,
                           std::vector<std::string> playerNames,
                           Course::ResourceMap startingResources)
{
    std::shared_ptr<ObjectManager> objMan = mapWindow->getObjMan();
    std::shared_ptr<GameEventHandler> GEHand = mapWindow->getGEHandler();

    // Generate tiles and draw them
    auto& worldGen = Course::WorldGenerator::getInstance();
    worldGen.addConstructor<Course::Forest>(10);
    worldGen.addConstructor<Course::Grassland>(10);
    unsigned int x = 10; // TODO: from player or hard coded?
    unsigned int y = 10; // TODO: from player or hard coded?
    unsigned int seed = 5; // TODO: random in final version
    worldGen.generateMap(x, y, seed, objMan, GEHand);
    std::vector<std::shared_ptr<Course::TileBase>> allTiles = objMan->getTiles();
    for(std::shared_ptr<Course::TileBase>& tile: allTiles){
        mapWindow->drawItem(tile);
    }

    // Generate players and save them
    std::shared_ptr<Player> player1Ptr = std::make_shared<Player>(playerNames[0]);
    std::shared_ptr<Player> player2Ptr = std::make_shared<Player>(playerNames[1]);
    objMan->addPlayer(player1Ptr);
    objMan->addPlayer(player2Ptr);


    GEHand->newModifyResources(player1Ptr, startingResources);
    GEHand->newModifyResources(player2Ptr, startingResources);

}

void GameEngine::startGame(MapWindow *mapWindow, std::shared_ptr<ObjectManager> objMan)
{
        std::shared_ptr<GameEventHandler> GEHand = mapWindow->getGEHandler(); // TODO: needed?
        std::vector<std::shared_ptr<Player>> players = objMan->getPlayers();
        // Start the game by giving the turn to player 1
        GEHand->setPlayerInTurn(players[0]);
        mapWindow->changeTurn(players[0]);
}

void GameEngine::endGame(MapWindow *mapWindow, std::vector<std::shared_ptr<Player>> winners)
{
    // Popup dialog?
    // Different cases for a win and a draw
}
