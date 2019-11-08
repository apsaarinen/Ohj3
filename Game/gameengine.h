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
    GameEngine();
    void setupGame(MapWindow* mapWindow, std::shared_ptr<ObjectManager> objMan, std::shared_ptr<GameEventHandler> GEHand);
};

#endif // GAMEENGINE_H
