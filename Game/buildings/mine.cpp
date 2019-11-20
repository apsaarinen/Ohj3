#include "mine.hh"

Mine::Mine(const std::shared_ptr<GameEventHandler>& eventhandler,
           const std::shared_ptr<ObjectManager>& objectmanager,
           const std::shared_ptr<Player>& owner,
           const int& tilespaces,
           const Course::ResourceMap& buildcost,
           const Course::ResourceMap& production
           ):
    BuildingBase(
        eventhandler,
        objectmanager,
        owner,
        tilespaces,
        buildcost,
        production
        )
{
}

std::string Mine::getType() const
{
    return "Mine";
}
