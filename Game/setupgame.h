#ifndef SETUPGAME_H
#define SETUPGAME_H

#include "ui/mapwindow.hh"
#include "core/player.h"
#include "core/objectmanager.h"
#include "core/worldgenerator.h"
#include "tiles/tilebase.h"
#include "tiles/forest.h"
#include "tiles/grassland.h"
#include "tiles/blockfield.h"
#include "tiles/water.h"
#include "tiles/oredeposit.h"

namespace Game {

/**
 * @brief Sets up the game to be played. \n
 * Creates tiles, player and sets their resources
 * @param mapWindow the main game window
 * @param playerNames the selected names for both players
 * @param startingResources amount of resources the players start with
 * @param objMan the ObjectManager
 * @note Doesn't need to be a class so is a separate function
 */
void setupGame(MapWindow *mapWindow,
               std::vector<std::string> playerNames,
               Course::ResourceMap startingResources,
               std::shared_ptr<ObjectManager> objMan);

} // namespace Game

#endif // SETUPGAME_H
