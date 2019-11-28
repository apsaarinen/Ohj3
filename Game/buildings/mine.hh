#ifndef MINE_HH
#define MINE_HH

#include "buildings/buildingbase.h"
#include "core/resourcemaps.h"
#include "core/gameeventhandler.h"
#include "core/objectmanager.h"
#include "core/player.h"
#include "core/resourcemaps_v2.hh"

namespace Game {

/**
 * @brief The Mine class represents a mine-building in the game.
 *
 * The mine adds 1 base-production for money and 5 for stone and ore.
 */
class Mine : public Course::BuildingBase
{
public:
    /**
     * @brief Disabled parameterless constructor.
     */
    Mine() = delete;

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
    explicit Mine(
            const std::shared_ptr<GameEventHandler>& eventhandler,
            const std::shared_ptr<ObjectManager>& objectmanager,
            const std::shared_ptr<Player>& owner,
            const int& tilespaces = 1,
            const Course::ResourceMap& buildcost = Game::ConstResourceMaps::MINE_BUILD_COST,
            const Course::ResourceMap& production = Game::ConstResourceMaps::MINE_PRODUCTION
            );

    /**
     * @brief Default destructor.
     */
    virtual ~Mine() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;
};

} // namespace Game

#endif // MINE_HH
