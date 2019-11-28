#ifndef BLOCKFIELD_H
#define BLOCKFIELD_H

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
 * @brief The Blockfield class represents a blockfield in the gameworld.
 *
 * Blockfield has BasicProduction: \n
 * * Money = 2
 * * Food = 0
 * * Wood = 0
 * * Stone = 5
 * * Ore = 2
 *
 * Building in the blockfield takes time. So buildings get extra hold-marker.
 *
 * Tile supports 3 buildings.
 */
class Blockfield : public Course::TileBase
{
public:
    /**
     * @brief Disabled parameterless constructor.
     */
    Blockfield() = delete;

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
    Blockfield(const Course::Coordinate& location,
           const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
           const std::shared_ptr<Course::iObjectManager>& objectmanager,
           const unsigned int& max_build = 3,
           const unsigned int& max_work = 3,
           const Course::ResourceMap& production = Game::ConstResourceMaps::BLOCKFIELD_BP);
    /**
     * @brief Default destructor.
     */
    virtual ~Blockfield() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;

    /**
     * @brief Adds a new building-object to the tile. Building in blockfield adds
     * one hold-marker to the building.
     *
     * Phases: \n
     * 1. Check that there is space for the building. \n
     * 2. Call parent's addBuilding \n
     * 3. Add a HoldMarker for the building. \n
     *
     * @post Exception guarantee: Strong
     * @exception OwnerConflict - If the tile's ownership prevents placing the
     * \b building.
     * @exception NoSpace - If the tile doesn't have enough space for
     * the \b building.
     */
    void addBuilding(const std::shared_ptr<Course::BuildingBase>& building) override;

};

} // namespace Game

#endif // BLOCKFIELD_H
