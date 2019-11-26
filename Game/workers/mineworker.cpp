#include "mineworker.h"
#include "tiles/tilebase.h"
#include "interfaces/igameeventhandler.h"
#include "interfaces/iobjectmanager.h"

MineWorker::MineWorker(const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
                       const std::shared_ptr<Course::iObjectManager> &objectmanager,
                       const std::shared_ptr<Course::PlayerBase> &owner,
                       const int &tilespaces, const Course::ResourceMap &cost,
                       const Course::ResourceMapDouble &efficiency):
    WorkerBase(
        eventhandler,
        objectmanager,
        owner,
        tilespaces,
        cost,
        efficiency)
{
}

std::string MineWorker::getType() const
{
    return "MineWorker";
}

bool MineWorker::canBePlacedOnTile(const std::shared_ptr<Course::TileBase> &target) const
{
    return target->getOwner() == getOwner() and
            WorkerBase::canBePlacedOnTile(target);
}

void MineWorker::doSpecialAction()
{

}

const Course::ResourceMapDouble MineWorker::tileWorkAction()
{
    auto player = getOwner();
    auto events = lockEventHandler();
    double satisfaction = 0;
    Course::BasicResource focus = getResourceFocus();

    Course::ResourceMapDouble final_modifier;

    if ( events->modifyResource(player, Course::BasicResource::FOOD, -2) )
    {
        satisfaction = 0.5;
        if ( events->modifyResource(player, Course::BasicResource::MONEY, -2) )
        {
            satisfaction = 1;
        }
    }


    if( focus != Course::BasicResource::NONE )
    {
        final_modifier[focus] =
                WORKER_EFFICIENCY.at(focus) * (satisfaction + 0.25);
    }
    else
    {
        for( auto it = WORKER_EFFICIENCY.begin();
             it != WORKER_EFFICIENCY.end();
             ++it )
        {
            final_modifier[it->first] = it->second * satisfaction;
        }
    }

    return final_modifier;
}

