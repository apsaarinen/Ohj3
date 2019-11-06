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


class GameEngine
{
public:
    GameEngine();
    void setupGame();
};

#endif // GAMEENGINE_H
