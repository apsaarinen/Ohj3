#ifndef SAWMILL_HH
#define SAWMILL_HH

#include "buildings/buildingbase.h"
#include "core/resourcemaps.h"
#include "gameeventhandler.h"
#include "objectmanager.h"
#include "player.h"
#include "resourcemaps_v2.hh"

/**
 * @brief The Sawmill class represents a sawmill-building in the game.
 *
 * The sawmill adds 1 base-production for money, 2 for food and 5 for wood.
 */
class SawMill : public Course::BuildingBase
{
public:
    /**
     * @brief Disabled parameterless constructor.
     */
    SawMill() = delete;

    /**
     * @brief Constructor for the class.
     *
     * @param eventhandler points to the student's GameEventHandler.
     * @param owner points to the owning player.
     * @param tile points to the tile upon which the building is constructed.
     *
     * @post Exception Guarantee: No guarantee.
     * @exception OwnerConflict - if the building conflicts with tile's
     * ownership.
     */
    explicit SawMill(
            const std::shared_ptr<GameEventHandler>& eventhandler,
            const std::shared_ptr<ObjectManager>& objectmanager,
            const std::shared_ptr<Player>& owner,
            const int& tilespaces = 1,
            const Course::ResourceMap& buildcost = Course::ConstResourceMaps::SAWMILL_BUILD_COST,
            const Course::ResourceMap& production = Course::ConstResourceMaps::SAWMILL_PRODUCTION
            );

    /**
     * @brief Default destructor.
     */
    virtual ~SawMill() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;
};

#endif // SAWMILL_HH
