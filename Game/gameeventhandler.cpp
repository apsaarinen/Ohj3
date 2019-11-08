#include "gameeventhandler.h"

GameEventHandler::GameEventHandler()
{

}

bool GameEventHandler::modifyResource(std::shared_ptr<Course::PlayerBase> player, Course::BasicResource resource, int amount)
{

}

bool GameEventHandler::modifyResources(std::shared_ptr<Course::PlayerBase> player, Course::ResourceMap resources)
{

}

bool GameEventHandler::newModifyResource(std::shared_ptr<Player> player, Course::BasicResource resource, int amount)
{
    return player->modifyResource(resource, amount);
}

bool GameEventHandler::newModifyResources(std::shared_ptr<Player> player, Course::ResourceMap resources)
{
    return player->modifyResources(resources);
}
