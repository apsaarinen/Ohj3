#ifndef PLAYER_H
#define PLAYER_H

#include "core/playerbase.h"
#include "core/basicresources.h"

class Player : public Course::PlayerBase
{
public:
    /**
     * @brief Constructor for the class
     * @param name A std::string for player's name
     * @param objects (optional) A std::vector of shared-pointers to
     * GameObjects.
     */
    Player(const std::string& name,
               const std::vector<std::shared_ptr<Course::GameObject> > objects ={});

    bool modifyResource(const Course::BasicResource& resource, const int& amount);
    bool modifyResources(const Course::ResourceMap &resources);
private:
    Course::ResourceMap m_resources;

};

#endif // PLAYER_H
