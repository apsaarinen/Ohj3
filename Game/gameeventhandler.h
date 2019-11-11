#ifndef GAMEEVENTHANDLER_H
#define GAMEEVENTHANDLER_H

#include <QWidget>
#include "interfaces/igameeventhandler.h"
#include "core/basicresources.h"
#include "player.h"
#include "objectmanager.h"

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
    bool newModifyResource(std::shared_ptr<Player> player, Course::BasicResource resource, int amount);

    /**
     * @brief Modify Player's resources. Can be used to both sum or subtract
     * @param player Pointer to the Player whose resources are being modified.
     * @param resources ResourceMap containing change amounts.
     * @return
     * True - Modification was succesful. \n
     * False - Modification failed. \n
     */
    bool newModifyResources(std::shared_ptr<Player> player, Course::ResourceMap resources);

    // Check if player has won the game
    bool playerHasWon(std::shared_ptr<Player> player);

    // Calculate income for both of the players and add it to their resources
    void addIncome(std::shared_ptr<ObjectManager> objMan);

private:

    int m_winningResources; // TODO: this has to be set up in the beginning
    
};

#endif // GAMEEVENTHANDLER_H
