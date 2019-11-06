#include "objectmanager.h"

ObjectManager::ObjectManager()
{

}

void ObjectManager::addTiles(const std::vector<std::shared_ptr<Course::TileBase> > &tiles)
{
    m_tiles = tiles;
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

std::vector<std::shared_ptr<Course::TileBase>> ObjectManager::getTiles()
{
    std::vector<std::shared_ptr<Course::TileBase>> matchingTiles;
    for(std::shared_ptr<Course::TileBase> tile: m_tiles) {
        matchingTiles.push_back(tile);
    }
    return matchingTiles;
}
