#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "mapwindow.hh"
#include "begindialog.hh"
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
    void setupGame(MapWindow* mapWindow, std::vector<std::string> playerNames, Course::ResourceMap startingResources);
    // Start the game for the QT event loop
    void startGame(MapWindow* mapWindow, std::shared_ptr<ObjectManager> objMan);

private:
    // End dialog (player name, stats, etc.)
    void endGame(MapWindow* mapWindow, std::vector<std::shared_ptr<Player> > winners);

};

#endif // GAMEENGINE_H
