#include "gameengine.h"

GameEngine::GameEngine()
{

}

void GameEngine::setupGame(MapWindow *mapWindow,
                           std::shared_ptr<ObjectManager> objMan,
                           std::shared_ptr<GameEventHandler> GEHand)
{
    mapWindow->setGEHandler(GEHand); // TODO: what is this used for

    // Open dialog window(?) and ask for game specs
    // TODO

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
    std::shared_ptr<Player> player1Ptr = std::make_shared<Player>("Player1"); // TODO: player name
    std::shared_ptr<Player> player2Ptr = std::make_shared<Player>("Player2"); // TODO: player name
    objMan->addPlayer(player1Ptr);
    objMan->addPlayer(player2Ptr);

    // Set up player resources
    Course::ResourceMap startResources = {
        {Course::BasicResource::MONEY, 100},
        {Course::BasicResource::FOOD, 100},
        {Course::BasicResource::WOOD, 100},
        {Course::BasicResource::STONE, 100},
        {Course::BasicResource::ORE, 100},
    }; // TODO: get starting resource amounts from start dialog window
    GEHand->newModifyResources(player1Ptr, startResources);
    GEHand->newModifyResources(player2Ptr, startResources);

    // TODO: Get the win condition from setup dialog and save it to eventhander or somewhere

}

void GameEngine::turnManager(MapWindow *mapWindow, std::shared_ptr<ObjectManager> objMan)
{
    std::shared_ptr<GameEventHandler> GEHand = mapWindow->getGEHandler(); // TODO: needed?
    std::vector<std::shared_ptr<Player>> players = objMan->getPlayers();
    while(true) {

        // Add income and running costs for players
        GEHand->addIncome(objMan);

        // Check for win condition for both players
        std::vector<std::shared_ptr<Player>> winners = checkWinCondition(GEHand, players);
        // We have winner(s)
        if(winners.size() > 0) {
            endGame(mapWindow, winners);
            return;
        }
        // Else: No winners --> continue the game

        for(std::shared_ptr<Player> player: players) {
            playerTurn(mapWindow, player);
        }
    }
}

void GameEngine::playerTurn(MapWindow *mapWindow, std::shared_ptr<Player> player)
{
    // Player turn flow:

    // Player turn starts

    // Update UI for player in turn

    // Let the player make changes to a tile

    // Player chooses to end their turn

    // Player turn ends

}

void GameEngine::endGame(MapWindow *mapWindow, std::vector<std::shared_ptr<Player>> winners)
{
    // Popup dialog?
    // Different cases for a win and a draw
}

std::vector<std::shared_ptr<Player> > GameEngine::checkWinCondition(std::shared_ptr<GameEventHandler> GEHand, std::vector<std::shared_ptr<Player> > players)
{
    std::vector<std::shared_ptr<Player>> winners;
    for(std::shared_ptr<Player> player: players) {
        if(GEHand->playerHasWon(player)) {
            winners.push_back(player);
        }
    }
    return winners;
}
