#ifndef GAMEEVENTHANDLER_H
#define GAMEEVENTHANDLER_H

#include "interfaces/igameeventhandler.h"
#include "core/basicresources.h"
#include "core/player.h"
#include "core/objectmanager.h"
#include "core/resourcemaps_v2.hh"

namespace Game {

/**
 * @brief The GameEventHandler class controls and stores the game's status.
 *
 * Only one of these should exists at any given point in the time
 */
class GameEventHandler : public Course::iGameEventHandler
{
public:
    /**
     * @brief Constructor for the class.
     */
    GameEventHandler();

    /**
     * @brief Modify Player's resource. Can be used to both sum or subtract.
     * @param player Pointer to the Player whose resource is being modified.
     * @param resource Defines the modified resource.
     * @param amount Defines the amount of change.
     * @post Exception guarantee: Basic
     * @return
     * True - Modification was succesful. \n
     * False - Modification failed. \n
     */
    bool modifyResource(std::shared_ptr<Course::PlayerBase> player,
                        Course::BasicResource resource,
                        int amount);

    /**
     * @brief Modify Player's resources. Can be used to both sum or subtract
     * @param player Pointer to the Player whose resources are being modified.
     * @param resources ResourceMap containing change amounts.
     * @return
     * True - Modification was succesful. \n
     * False - Modification failed. \n
     */
    bool modifyResources(std::shared_ptr<Course::PlayerBase> player,
                         Course::ResourceMap resources);

    /**
     * @brief Gets the player in turn
     * @return the player whose turn it is currently
     */
    std::shared_ptr<Player> getPlayerInTurn();

    /**
     * @brief Sets the player in turn
     * @param player Pointer to the Player.
     */
    void setPlayerInTurn(const std::shared_ptr<Player> player);

    /**
     * @brief Checks if players have won
     * @param players Vector of pointers to Player objects.
     * @return Vector of pointers to Player objects that have won
     */
    std::vector<std::shared_ptr<Player>> checkWinCondition(
            std::vector<std::shared_ptr<Player>> players);

    /**
     * @brief Sets the sum of resources needed to win the game
     * @param resourcesToWin Amount of resources as a sum
     */
    void setResourcesToWin(const int resourcesToWin);

    /**
     * @brief Sets the flag telling that we are in the middle of buying something
     * @param buying Flag for buying
     */
    void setBuyingFlag(const bool buying);

    /**
     * @brief Checks if we are in the middle of buying something
     * @return Boolean value telling if we are buying something
     */
    bool isPlayerBuying() const;

    /**
     * @brief Gets the amount of rounds the game has been played
     * @return Amount of rounds
     */
    int getRounds() const;

    /**
     * @brief Increases the game round by one
     * @return Amount of rounds after the increase
     */
    int increaseRounds();

private:
    /**
     * @brief Checks if a player has won
     * @param player Pointer to the Player.
     * @return
     * True - Player has won. \n
     * False - Player hasn't won. \n
     */
    bool playerHasWon(std::shared_ptr<Player> player);

    int m_rounds = 1;
    int m_resourcesToWin;
    std::weak_ptr<Player> m_playerInTurn;
    bool m_playerBuying = false;
};

} // namespace Game

#endif // GAMEEVENTHANDLER_H
