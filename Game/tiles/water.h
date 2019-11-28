#ifndef WATER_H
#define WATER_H

#include "tiles/tilebase.h"
#include "core/gameeventhandler.h"
#include "core/objectmanager.h"
#include "core/coordinate.h"
#include "core/resourcemaps.h"
#include "core/resourcemaps_v2.hh"
#include "core/basicresources.h"
#include "buildings/buildingbase.h"

namespace Game {

/**
 * @brief The Water class represents water in the gameworld.
 *
 * Water has BasicProduction: \n
 * * Money = 0
 * * Food = 0
 * * Wood = 0
 * * Stone = 0
 * * Ore = 0
 *
 * You cannot build in water!
 */
class Water : public Course::TileBase
{
public:
    /**
     * @brief Disabled parameterless constructor.
     */
    Water() = delete;

    /**
     * @brief Constructor for the class.
     *
     * @param location is the Coordinate where the Tile is located in the game.
     * @param eventhandler points to the GameEventHandler.
     * @param objectmanager points to the ObjectManager.
     * @param max_build defines maximum amount of buildings on the tile
     * @param max_work defines maximum amount of workers on the tile
     * @param production sets the tiles production
     */
    Water(const Course::Coordinate& location,
           const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
           const std::shared_ptr<Course::iObjectManager>& objectmanager,
           const unsigned int& max_build = 0,
           const unsigned int& max_work = 0,
           const Course::ResourceMap& production = Game::ConstResourceMaps::WATER_BP);

    /**
     * @brief Default destructor.
     */
    virtual ~Water() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;

};

} // namespace Game

#endif // WATER_H
