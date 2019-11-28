#include "objectmanager.h"

namespace Game {

ObjectManager::ObjectManager()
{

}

void ObjectManager::addTiles(const std::vector<std::shared_ptr<Course::TileBase> > &tiles)
{
    m_tiles.insert(m_tiles.end(), tiles.begin(), tiles.end());
}

std::shared_ptr<Course::TileBase> ObjectManager::getTile(const Course::Coordinate& coordinate)
{
    for(std::shared_ptr<Course::TileBase> tile: m_tiles) {
        if(coordinate.x() == tile->getCoordinatePtr()->x() and
                coordinate.y() == tile->getCoordinatePtr()->y()) {
            return tile;
        }
    }
    return nullptr;
}

std::shared_ptr<Course::TileBase> ObjectManager::getTile(const Course::ObjectId& id)
{
    for(std::shared_ptr<Course::TileBase> tile: m_tiles) {
        if(tile->ID == id) {
            return tile;
        }
    }
    return nullptr;
}

std::vector<std::shared_ptr<Course::TileBase>> ObjectManager::getTiles(const std::vector<Course::Coordinate>& coordinates)
{
    std::vector<std::shared_ptr<Course::TileBase>> matchingTiles;
    for(Course::Coordinate coordinate: coordinates) {
        for(std::shared_ptr<Course::TileBase> tile: m_tiles) {
            if(coordinate.x() == tile->getCoordinatePtr()->x() and
                    coordinate.y() == tile->getCoordinatePtr()->y()) {
                matchingTiles.push_back(tile);
            }
        }
    }
    return matchingTiles;
}

const std::vector<std::shared_ptr<Course::TileBase>> ObjectManager::getTiles() const
{
    return m_tiles;
}

void ObjectManager::addPlayer(const std::shared_ptr<Player> player)
{
    m_players.push_back(player);
}

const std::vector<std::shared_ptr<Player> > ObjectManager::getPlayers() const
{
    return m_players;
}

bool ObjectManager::isLastPlayer(const std::shared_ptr<Player> player)
{
    return m_players.back() == player;
}

void ObjectManager::addPlaceableObject(const std::shared_ptr<Course::PlaceableGameObject> object)
{
    m_placeableObjects.push_back(object);
}

const std::shared_ptr<Course::PlaceableGameObject> ObjectManager::getNewestPlaceableObject()
{
    if(m_placeableObjects.size() > 0) {
        return m_placeableObjects.back();
    }
    else {
        return nullptr;
    }
}

} // namespace Game
