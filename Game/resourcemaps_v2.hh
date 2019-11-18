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
    {BasicResource::MONEY, 2},
    {BasicResource::STONE, 10},
    {BasicResource::ORE, 10}
};

// Building - Sawmill
const ResourceMap SAWMILL_BUILD_COST = {
    {BasicResource::MONEY, 70},
    {BasicResource::FOOD, 70},
    {BasicResource::WOOD, 50}
};
const ResourceMap SAWMILL_PRODUCTION = {
    {BasicResource::MONEY, 1},
    {BasicResource::FOOD, 5},
    {BasicResource::WOOD, 10}
};

// Worker - SawMillWorker
const ResourceMapDouble SMW_WORKER_EFFICIENCY = {
    {MONEY, 0.25},
    {FOOD, 0.25},
    {WOOD, 2.00},
    {STONE, 0.25},
    {ORE, 0.25}
};
const ResourceMap SMW_RECRUITMENT_COST = {
    {MONEY, 20},
    {FOOD, 50}
};

// Worker - MineWorker
const ResourceMapDouble MW_WORKER_EFFICIENCY = {
    {MONEY, 0.25},
    {FOOD, 0.25},
    {WOOD, 0.25},
    {STONE, 1.50},
    {ORE, 1.50}
};
const ResourceMap MW_RECRUITMENT_COST = {
    {MONEY, 20},
    {FOOD, 50}
};

// Tile - Blockfield
const ResourceMap BLOCKFIELD_BP = {
    {MONEY, 2},
    {FOOD, 0},
    {WOOD, 0},
    {STONE, 5},
    {ORE, 2},
};

// Tile - OreDeposit
const ResourceMap OREDEPOSIT_BP = {
    {MONEY, 3},
    {FOOD, 0},
    {WOOD, 0},
    {STONE, 2},
    {ORE, 5},
};

// Tile - Water
// NOTE: Water doesn't produce resources
const ResourceMap WATER_BP = {
    {MONEY, 0},
    {FOOD, 0},
    {WOOD, 0},
    {STONE, 0},
    {ORE, 0},
};

}
}

#endif // RESOURCEMAPS_V2_HH
