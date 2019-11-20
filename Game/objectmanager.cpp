#include "objectmanager.h"

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
        if(coordinate.x() == tile->getCoordinatePtr()->x() and coordinate.y() == tile->getCoordinatePtr()->y()) {
            return tile;
        }
    }
    return nullptr; // TODO: Is this ok?
}

std::shared_ptr<Course::TileBase> ObjectManager::getTile(const Course::ObjectId& id)
{
    for(std::shared_ptr<Course::TileBase> tile: m_tiles) {
        if(tile->ID == id) {
            return tile;
        }
    }
    return nullptr; // TODO: Is this ok?
}


std::vector<std::shared_ptr<Course::TileBase>> ObjectManager::getTiles(const std::vector<Course::Coordinate>& coordinates)
{
    std::vector<std::shared_ptr<Course::TileBase>> matchingTiles;
    for(Course::Coordinate coordinate: coordinates) {
        for(std::shared_ptr<Course::TileBase> tile: m_tiles) {
            if(coordinate.x() == tile->getCoordinatePtr()->x() and coordinate.y() == tile->getCoordinatePtr()->y()) {
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

std::vector<std::shared_ptr<Course::TileBase> > ObjectManager::getTiles(const std::shared_ptr<Player> player) const
{
    std::vector<std::shared_ptr<Course::TileBase>> tiles;
    for(std::shared_ptr<Course::TileBase> tile: m_tiles) {
        if(tile->getOwner() == player) {
            tiles.push_back(tile);
        }
    }
    return tiles;
}

void ObjectManager::addPlayer(const std::shared_ptr<Player> player)
{
    m_players.push_back(player);
}

void ObjectManager::addPlayers(const std::vector<std::shared_ptr<Player> > &players)
{
    m_players.insert(m_players.end(), players.begin(), players.end());
}

std::shared_ptr<Player> ObjectManager::getPlayer(const std::string &name)
{
    for(std::shared_ptr<Player>& player: m_players) {
        if(player->getName() == name) {
            return player;
        }
    }
    return nullptr;
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

const std::vector<std::shared_ptr<Course::PlaceableGameObject> > ObjectManager::getPlaceableObjects() const
{
    return m_placeableObjects;
}

const std::shared_ptr<Course::PlaceableGameObject> ObjectManager::getPlaceableObject(const Course::ObjectId &id)
{
    for(std::shared_ptr<Course::PlaceableGameObject>& obj: m_placeableObjects) {
        if(obj->ID == id) {
            return obj;
        }
    }
    return nullptr;
}

const std::shared_ptr<Course::PlaceableGameObject> ObjectManager::getNewestPlaceableObject()
{
    return m_placeableObjects.back();
}
