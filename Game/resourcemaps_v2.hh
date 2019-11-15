#ifndef RESOURCEMAPS_V2_HH
#define RESOURCEMAPS_V2_HH

#include "core/basicresources.h"

namespace Course{

namespace ConstResourceMaps {

// Building - Mine
const ResourceMap MINE_BUILD_COST = {
    {BasicResource::MONEY, 60},
    {BasicResource::FOOD, 80},
    {BasicResource::WOOD, 30}
};
const ResourceMap MINE_PRODUCTION = {
    {BasicResource::MONEY, 1},
    {BasicResource::FOOD, 5},
    // TODO: Basic production for Mine depending on tile?
};

// Building - Sawmill
const ResourceMap SawMill_BUILD_COST = {
    {BasicResource::MONEY, 70},
    {BasicResource::FOOD, 70},
    {BasicResource::WOOD, 50}
};
const ResourceMap SawMill_PRODUCTION = {
    {BasicResource::MONEY, 1},
    {BasicResource::FOOD, 5},
    {BasicResource::WOOD, 2}
};
}
}

#endif // RESOURCEMAPS_V2_HH
