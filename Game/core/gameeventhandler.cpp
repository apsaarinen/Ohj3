#include "gameeventhandler.h"

namespace Game {

GameEventHandler::GameEventHandler()
{
}

bool GameEventHandler::modifyResource(std::shared_ptr<Course::PlayerBase> player, Course::BasicResource resource, int amount)
{
    std::shared_ptr<Player> playerNew = std::static_pointer_cast<Player>(player);
    if(playerNew != nullptr) {
        return playerNew->modifyResource(resource, amount);
    }
    return false;
}

bool GameEventHandler::modifyResources(std::shared_ptr<Course::PlayerBase> player, Course::ResourceMap resources)
{
    std::shared_ptr<Player> playerNew = std::static_pointer_cast<Player>(player);
    if(playerNew != nullptr) {
        return playerNew->modifyResources(resources);
    }
    return false;
}

bool GameEventHandler::playerHasWon(std::shared_ptr<Player> player)
{
    Course::ResourceMap playerResourceMap = player->getResources();
    int resourceSum = 0;
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

std::vector<std::shared_ptr<Player>> GameEventHandler::checkWinCondition(std::vector<std::shared_ptr<Player>> players)
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

void GameEventHandler::setBuyingFlag(const bool buying)
{
    m_playerBuying = buying;
}

bool GameEventHandler::isPlayerBuying() const
{
    return m_playerBuying;
}

int GameEventHandler::getRounds() const
{
    return m_rounds;
}

int GameEventHandler::increaseRounds()
{
    return ++m_rounds;
}

} // namespace Game
