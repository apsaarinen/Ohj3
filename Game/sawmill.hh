#ifndef SAWMILL_HH
#define SAWMILL_HH


#include "buildings/buildingbase.h"
#include "core/resourcemaps.h"
#include "gameeventhandler.h"
#include "objectmanager.h"
#include "player.h"

/**
 * @brief The Sawmill class represents a sawmill-building in the game.
 *
 * The sawmill adds 2 base-production for wood depending on the tile its placed on.
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
            const Course::ResourceMap& buildcost = Course::ConstResourceMaps::FARM_BUILD_COST,
            const Course::ResourceMap& production = Course::ConstResourceMaps::FARM_PRODUCTION
            );
            // TODO: SawMill_BUILD_COST ja SawMill_PRODUCTION
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
