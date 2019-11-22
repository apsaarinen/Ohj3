#ifndef WATER_H
#define WATER_H

#include "tiles/tilebase.h"
#include "gameeventhandler.h"
#include "objectmanager.h"
#include "core/coordinate.h"
#include "core/resourcemaps.h"
#include "resourcemaps_v2.hh"
#include "core/basicresources.h"
#include "buildings/buildingbase.h"

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
     * @param eventhandler points to the student's GameEventHandler.
     */
    Water(const Course::Coordinate& location,
           const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
           const std::shared_ptr<Course::iObjectManager>& objectmanager,
           const unsigned int& max_build = 0,
           const unsigned int& max_work = 0,
           const Course::ResourceMap& production = Course::ConstResourceMaps::WATER_BP);

    /**
     * @brief Default destructor.
     */
    virtual ~Water() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;

    // TODO: you can't build in water
    void addBuilding(const std::shared_ptr<Course::BuildingBase>& building) override;
};

#endif // WATER_H
