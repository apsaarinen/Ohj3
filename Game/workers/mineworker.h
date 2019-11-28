#ifndef MINEWORKER_H
#define MINEWORKER_H

#include "workers/workerbase.h"
#include "core/resourcemaps.h"
#include "core/resourcemaps_v2.hh"

namespace Game {

/**
 * @brief The MineWorker class represents a mine worker in the game.
 *
 * Worker has following production-efficiency: \n
 * * Money - 0.25 \n
 * * Food - 0.25 \n
 * * Wood - 0.25 \n
 * * Stone - 1.50 \n
 * * Ore - 1.50 \n
 *
 * MineWorkers consume Food and money. \n
 * * 2 Food - Or MineWorker refuses to work. \n
 * * 2 Money - Or MineWorker works at 50% efficiency.
 */
class MineWorker : public Course::WorkerBase
{
public:
    /**
     * @brief Disabled parameterless constructor.
     */
    MineWorker() = delete;

    /**
     * @brief Constructor for the class.
     *
     * @param eventhandler points to the student's GameEventHandler.
     * @param objectmanager points to the ObjectManager.
     * @param owner points to the owning player.
     * @param tilespaces defines how many spaces the worker takes on tile
     * @param cost defines how much the worker costs
     * @param efficiency defines how much and what the worker produces
     */
    MineWorker(const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
                const std::shared_ptr<Course::iObjectManager>& objectmanager,
                const std::shared_ptr<Course::PlayerBase>& owner,
                const int& tilespaces = 1,
                const Course::ResourceMap& cost =
                    Game::ConstResourceMaps::MW_RECRUITMENT_COST,
                const Course::ResourceMapDouble& efficiency =
                    Game::ConstResourceMaps::MW_WORKER_EFFICIENCY
                );

    /**
     * @brief Default destructor.
     */
    virtual ~MineWorker() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;

    /**
     * @brief Check if the worker can be placed on the Tile according to
     * it's placement rule. Only rule is that the Tile must have same owner
     * as the worker.
     * @param target is the Tile that worker is being placed on.
     * @return
     * True - If baseclass' method return true and target Tile has space
     * for worker.
     * False - If both conditions aren't met.
     * @note Override to change placement rules for derived worker.
     * @post Exception guarantee: Basic
     */
    virtual bool canBePlacedOnTile(
            const std::shared_ptr<Course::TileBase> &target) const override;

    /**
     * @brief Performs the Worker's default action.
     * Does nothing as this is not implemented.
     */
    virtual void doSpecialAction() override;

    /**
     * @brief Returns Worker's efficiency at resource production.
     * Worker consumes FOOD and MONEY. Resource consumption and resource
     * focus determine final multiplier that is based on WORKER_EFFICIENCY.
     *
     * @return
     */
    virtual const Course::ResourceMapDouble tileWorkAction() override;

};

} // namespace Game

#endif // MINEWORKER_H
