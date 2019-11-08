#include "player.h"

Player::Player(const std::string& name,
               const std::vector<std::shared_ptr<Course::GameObject> > objects):
    Course::PlayerBase(name, objects)
{

}

void Player::setResources(const Course::ResourceMap &startResources)
{
    m_resources = startResources;
}
