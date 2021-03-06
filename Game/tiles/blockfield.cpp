#include "blockfield.h"

namespace Game {

Blockfield::Blockfield(const Course::Coordinate &location,
                       const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
                       const std::shared_ptr<Course::iObjectManager> &objectmanager,
                       const unsigned int &max_build,
                       const unsigned int &max_work,
                       const Course::ResourceMap &production):
    TileBase(location,
             eventhandler,
             objectmanager,
             max_build,
             max_work,
             production)
{
}

std::string Blockfield::getType() const
{
    return "Blockfield";
}

void Blockfield::addBuilding(const std::shared_ptr<Course::BuildingBase> &building)
{
    TileBase::addBuilding(building);
    building->addHoldMarkers(1);
}

} // namespace Game
