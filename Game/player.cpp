#include "player.h"

Player::Player(const std::string& name,
               QColor color,
               const std::vector<std::shared_ptr<Course::GameObject> > objects):
    Course::PlayerBase(name, objects),
    m_color(color)
{

}

bool Player::modifyResource(const Course::BasicResource &resource, const int &amount)
{
    if(m_resources[resource]+amount < 0) {
        return false;
    }
    else {
        m_resources[resource] += amount;
        return true;
    }

}

bool Player::modifyResources(const Course::ResourceMap &resources)
{
    Course::ResourceMap newMap = Course::mergeResourceMaps(m_resources, resources);
    for(auto r: newMap) {
        if( r.second < 0) {
            return false;
        }
    }
    m_resources = newMap;
    return true;
}

Course::ResourceMap Player::getResources() const
{
    return m_resources;
}

const QColor Player::getColor() const
{
    return m_color;
}
