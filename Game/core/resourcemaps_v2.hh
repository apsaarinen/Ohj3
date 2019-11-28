#ifndef RESOURCEMAPS_V2_HH
#define RESOURCEMAPS_V2_HH

#include "core/basicresources.h"

namespace Game{

namespace ConstResourceMaps {

// All negative resourcemapdouble for additive inversion of other maps
const Course::ResourceMapDouble NEGATIVE = {
    {Course::MONEY, -1},
    {Course::FOOD, -1},
    {Course::WOOD, -1},
    {Course::STONE, -1},
    {Course::ORE, -1}
};

// Building - Mine
const Course::ResourceMap MINE_BUILD_COST = {
    {Course::BasicResource::MONEY, 60},
    {Course::BasicResource::FOOD, 80},
    {Course::BasicResource::WOOD, 30}
};
const Course::ResourceMap MINE_PRODUCTION = {
    {Course::BasicResource::MONEY, 1},
    {Course::BasicResource::STONE, 5},
    {Course::BasicResource::ORE, 5}
};

// Building - Sawmill
const Course::ResourceMap SAWMILL_BUILD_COST = {
    {Course::BasicResource::MONEY, 70},
    {Course::BasicResource::FOOD, 70},
    {Course::BasicResource::WOOD, 50}
};
const Course::ResourceMap SAWMILL_PRODUCTION = {
    {Course::BasicResource::MONEY, 1},
    {Course::BasicResource::FOOD, 2},
    {Course::BasicResource::WOOD, 5}
};

// Worker - SawMillWorker
const Course::ResourceMapDouble SMW_WORKER_EFFICIENCY = {
    {Course::MONEY, 0.25},
    {Course::FOOD, 0.25},
    {Course::WOOD, 2.00},
    {Course::STONE, 0.25},
    {Course::ORE, 0.25}
};
const Course::ResourceMap SMW_RECRUITMENT_COST = {
    {Course::MONEY, 20},
    {Course::FOOD, 50}
};

// Worker - MineWorker
const Course::ResourceMapDouble MW_WORKER_EFFICIENCY = {
    {Course::MONEY, 0.25},
    {Course::FOOD, 0.25},
    {Course::WOOD, 0.25},
    {Course::STONE, 1.50},
    {Course::ORE, 1.50}
};
const Course::ResourceMap MW_RECRUITMENT_COST = {
    {Course::MONEY, 20},
    {Course::FOOD, 50}
};

// Tile - Blockfield
const Course::ResourceMap BLOCKFIELD_BP = {
    {Course::MONEY, 2},
    {Course::FOOD, 0},
    {Course::WOOD, 0},
    {Course::STONE, 5},
    {Course::ORE, 2}
};

// Tile - OreDeposit
const Course::ResourceMap OREDEPOSIT_BP = {
    {Course::MONEY, 3},
    {Course::FOOD, 0},
    {Course::WOOD, 0},
    {Course::STONE, 2},
    {Course::ORE, 5}
};

// Tile - Water
// NOTE: Water doesn't produce resources
const Course::ResourceMap WATER_BP = {
    {Course::MONEY, 0},
    {Course::FOOD, 0},
    {Course::WOOD, 0},
    {Course::STONE, 0},
    {Course::ORE, 0}
};

}
}

#endif // RESOURCEMAPS_V2_HH
