#ifndef BLOCKFIELD_H
#define BLOCKFIELD_H

#include "tiles/tilebase.h"
#include "gameeventhandler.h"
#include "objectmanager.h"
#include "core/coordinate.h"
#include "core/resourcemaps.h"
#include "resourcemaps_v2.hh"
#include "core/basicresources.h"
#include "buildings/buildingbase.h"

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
     * @param eventhandler points to the student's GameEventHandler.
     */
    Blockfield(const Course::Coordinate& location,
           const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
           const std::shared_ptr<Course::iObjectManager>& objectmanager,
           const unsigned int& max_build = 2,
           const unsigned int& max_work = 3,
           const Course::ResourceMap& production = Course::ConstResourceMaps::BLOCKFIELD_BP);
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

#endif // BLOCKFIELD_H
