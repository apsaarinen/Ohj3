#ifndef SAWMILLWORKER_H
#define SAWMILLWORKER_H

#include "workers/workerbase.h"
#include "core/resourcemaps.h"
#include "resourcemaps_v2.hh"

/**
 * @brief The SawMillWorker class represents a saw mill worker in the game.
 *
 * Worker has following production-efficiency: \n
 * * Money - 0.25 \n
 * * Food - 0.25 \n
 * * Wood - 2.00 \n
 * * Stone - 0.25 \n
 * * Ore - 0.25 \n
 *
 * SawMillWorker consume Food and money. \n
 * * 2 Food - Or SawMillWorker refuses to work. \n
 * * 2 Money - Or SawMillWorker works at 50% efficiency.
 */
class SawMillWorker : public Course::WorkerBase
{
public:
    /**
     * @brief Disabled parameterless constructor.
     */
    SawMillWorker() = delete;

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
    SawMillWorker(const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
                const std::shared_ptr<Course::iObjectManager>& objectmanager,
                const std::shared_ptr<Course::PlayerBase>& owner,
                const int& tilespaces = 1,
                const Course::ResourceMap& cost =
                    Course::ConstResourceMaps::SMW_RECRUITMENT_COST,
                const Course::ResourceMapDouble& efficiency =
                    Course::ConstResourceMaps::SMW_WORKER_EFFICIENCY
                );

    /**
     * @brief Default destructor.
     */
    virtual ~SawMillWorker() = default;

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

private:
};

#endif // SAWMILLWORKER_H
