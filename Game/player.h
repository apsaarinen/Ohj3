#ifndef PLAYER_H
#define PLAYER_H

#include "core/playerbase.h"
#include "core/basicresources.h"
#include <QString>

/**
 * @brief The Player class represents a player in the game.
 *
 * Player has a name, color and ownership to GameObjects
 */
class Player : public Course::PlayerBase
{
public:
    /**
     * @brief Constructor for the class
     * @param name A std::string for player's name
     * @param color Player's color in the game as a string
     * @param objects (optional) A std::vector of shared-pointers to
     * GameObjects.
     */
    Player(const std::string& name,
           QString color,
           const std::vector<std::shared_ptr<Course::GameObject> > objects ={});

    /**
     * @brief Modifies a players resource (by addition)
     * @param resource A BasicResource type that is modified
     * @param amount Amount of that resource
     * @return Bool that tells if the operation was successful
     */
    bool modifyResource(const Course::BasicResource& resource,
                        const int& amount);

    /**
     * @brief Modifies a players resources (by addition)
     * @param resources A ResourceMap that is added to players resources
     * @return Bool that tells if the operation was successful
     */
    bool modifyResources(const Course::ResourceMap &resources);

    /**
     * @brief Returns the player's resources
     * @return ResourceMap containing players resources
     */
    Course::ResourceMap getResources() const;

    /**
     * @brief Returns the player's color
     * @return Qstring that tells the player's color
     */
    const QString getColor() const;

private:
    Course::ResourceMap m_resources;
    QString m_color;

};

#endif // PLAYER_H
