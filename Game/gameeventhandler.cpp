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
    if(player != nullptr) { // TODO: nullptr ok?
        return player->modifyResource(resource, amount);
    }
    return false;
}

bool GameEventHandler::newModifyResources(std::shared_ptr<Player> player, Course::ResourceMap resources)
{
    if(player != nullptr) { // TODO: nullptr ok?
        return player->modifyResources(resources);
    }
    return false;
}

bool GameEventHandler::playerHasWon(std::shared_ptr<Player> player)
{
    Course::ResourceMap playerResourceMap = player->getResources();
    int resourceSum;
    for(auto n: playerResourceMap) {
        resourceSum += n.second;
    }
    if(resourceSum >= m_resourcesToWin) {
        return true;
    }
    return false;
}

std::shared_ptr<Player> GameEventHandler::getPlayerInTurn()
{
    return m_playerInTurn.lock();
}

void GameEventHandler::setPlayerInTurn(const std::shared_ptr<Player> player)
{
    m_playerInTurn = player;
}

void GameEventHandler::addIncome(std::shared_ptr<ObjectManager> objMan)
{
    std::vector<std::shared_ptr<Course::TileBase>> tiles = objMan->getTiles();
    for(std::shared_ptr<Course::TileBase> tile: tiles) {
        tile->generateResources();
    }
}

std::vector<std::shared_ptr<Player> > GameEventHandler::checkWinCondition(std::vector<std::shared_ptr<Player> > players)
{
    std::vector<std::shared_ptr<Player>> winners;
    for(std::shared_ptr<Player> player: players) {
        if(playerHasWon(player)) {
            winners.push_back(player);
        }
    }
    return winners;
}

void GameEventHandler::setResourcesToWin(const int resourcesToWin)
{
    m_resourcesToWin = resourcesToWin;
}
