#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "mapwindow.hh"
#include "gameengine.h"
#include "objectmanager.h"
#include "gameeventhandler.h"
#include "core/worldgenerator.h"
#include "tiles/tilebase.h"
#include "tiles/forest.h"
#include "tiles/grassland.h"
#include "graphics/simplegamescene.h"
#include "player.h"
#include "core/basicresources.h"
#include "core/resourcemaps.h"

class GameEngine
{
public:
    // TODO: docu
    GameEngine();
    // Create the initial game setup
    void setupGame(MapWindow* mapWindow, std::shared_ptr<ObjectManager> objMan, std::shared_ptr<GameEventHandler> GEHand);
    // Give players turns and monitor win condition
    void turnManager(MapWindow* mapWindow, std::shared_ptr<ObjectManager> objMan);

private:
    // Execute a player turn
    void playerTurn(MapWindow* mapWindow, std::shared_ptr<Player> player);
    // End dialog (player name, stats, etc.)
    void endGame(MapWindow* mapWindow, std::vector<std::shared_ptr<Player> > winners);
    // Check whether player(s) have fulfilled the win condition(s)
    std::vector<std::shared_ptr<Player>> checkWinCondition(std::shared_ptr<GameEventHandler> GEHand, std::vector<std::shared_ptr<Player>> players);
};

#endif // GAMEENGINE_H
