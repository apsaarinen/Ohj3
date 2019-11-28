#include "sawmill.hh"

namespace Game {

SawMill::SawMill(const std::shared_ptr<GameEventHandler>& eventhandler,
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

std::string SawMill::getType() const
{
    return "Sawmill";
}

} // namespace Game
