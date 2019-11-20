#ifndef GAMEEVENTHANDLER_H
#define GAMEEVENTHANDLER_H

#include <QWidget>
#include "interfaces/igameeventhandler.h"
#include "core/basicresources.h"
#include "player.h"
#include "objectmanager.h"
#include "resourcemaps_v2.hh"

class GameEventHandler : public Course::iGameEventHandler
{
public:
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
    bool modifyResource(std::shared_ptr<Course::PlayerBase> player, Course::BasicResource resource, int amount);

    /**
     * @brief Modify Player's resources. Can be used to both sum or subtract
     * @param player Pointer to the Player whose resources are being modified.
     * @param resources ResourceMap containing change amounts.
     * @return
     * True - Modification was succesful. \n
     * False - Modification failed. \n
     */
    bool modifyResources(std::shared_ptr<Course::PlayerBase> player, Course::ResourceMap resources);

    // Check if player has won the game
    bool playerHasWon(std::shared_ptr<Player> player);

    // Returns the player whose turn it is currently
    std::shared_ptr<Player> getPlayerInTurn();

    // Sets the turn to a player
    void setPlayerInTurn(const std::shared_ptr<Player> player);

    // Calculate income for both of the players and add it to their resources
    void addIncome(std::shared_ptr<ObjectManager> objMan);

    std::vector<std::shared_ptr<Player>> checkWinCondition(std::vector<std::shared_ptr<Player>> players);

    void setResourcesToWin(const int resourcesToWin);

    // Setting and getting if we are in the middle of buying something
    void setBuyingFlag(const bool buying);
    bool isPlayerBuying() const;
private:

    int m_resourcesToWin;
    std::weak_ptr<Player> m_playerInTurn;
    bool m_playerBuying = false;
};

#endif // GAMEEVENTHANDLER_H
