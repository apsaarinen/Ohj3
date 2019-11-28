#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "interfaces/iobjectmanager.h"
#include "tiles/tilebase.h"
#include "core/coordinate.h"
#include "core/gameobject.h"
#include "core/player.h"

namespace Game {

/**
 * @brief The ObjectManager class stores Players and GameObjects \n
 * (Tiles, Buildings and workers).
 *
 * Only one of these should exists at any given point in the time
 */
class ObjectManager : public Course::iObjectManager
{

public:
    /**
     * @brief Constructor for the class.
     */
    ObjectManager();

    /**
     * @brief Adds new tiles to the ObjectManager.
     * @param tiles a vector that contains the Tiles to be added.
     * @post The tile-pointers in the vector are stored in the ObjectManager.
     * Exception Guarantee: Basic
     */
    void addTiles(const std::vector<std::shared_ptr<Course::TileBase>>& tiles);

    /**
     * @brief Returns a shared pointer to a Tile that has specified coordinate.
     * @param coordinate Requested Tile's Coordinate
     * @return a pointer to a Tile that has the given coordinate.
     * If no for the coordinate exists, return empty pointer.
     * @post Exception Guarantee: Basic
     */
    std::shared_ptr<Course::TileBase> getTile(const Course::Coordinate& coordinate);

    /**
     * @brief Returns a shared pointer to a Tile that has specified ID
     * @param id Tile's ObjectId.
     * @return a pointer to the Tile that has the given ID
     * If no for the id exists, return empty pointer.
     * @post Exception Guarantee: Basic
     */
    std::shared_ptr<Course::TileBase> getTile(const Course::ObjectId& id);

    /**
     * @brief Returns a vector of shared pointers to Tiles specified by
     * a vector of Coordinates.
     * @param coordinates a vector of Coordinates for the requested Tiles
     * @return Vector of that contains pointers to Tile's that match
     * the coordinates. The vector is empty if no matches were made.
     * @post Exception Guarantee: Basic
     */
    std::vector<std::shared_ptr<Course::TileBase>> getTiles(
            const std::vector<Course::Coordinate>& coordinates);

    /**
     * @brief Returns a vector of shared pointers to all stored Tiles.
     * @return Vector that contains pointers to Tiles
     * @post Exception Guarantee: Basic
     */
    const std::vector<std::shared_ptr<Course::TileBase> > getTiles() const;

    /**
     * @brief Adds a new Player to the ObjectManager.
     * @param player a pointer to a Player
     * @post The player-pointer is stored in the ObjectManager.
     * Exception Guarantee: Basic
     */
    void addPlayer(const std::shared_ptr<Player> player);

    /**
     * @brief Returns a vector of shared pointers to all stored Players.
     * @return Vector that contains pointers to Players
     * @post Exception Guarantee: Basic
     */
    const std::vector<std::shared_ptr<Player>> getPlayers() const;

    /**
     * @brief Returns whether a player is the last player to act
     * @param player a pointer to a Player
     * @return Bool that tells if the player is last to act
     * @post Exception Guarantee: Basic
     */
    bool isLastPlayer(const std::shared_ptr<Player> player);

    /**
     * @brief Adds a new PlaceableGameObject to the ObjectManager.
     * @param object a pointer to a PlaceableGameObject
     * @post The player-pointer is stored in the ObjectManager.
     * Exception Guarantee: Basic
     */
    void addPlaceableObject(const std::shared_ptr<Course::PlaceableGameObject> object);

    /**
     * @brief Returns a shared pointer to a PlaceableGameObject that \n
     * was last added
     * @return a pointer to a PlaceableGameObject that was last added
     * @post Exception Guarantee: Basic
     */
    const std::shared_ptr<Course::PlaceableGameObject> getNewestPlaceableObject();


private:
    std::vector<std::shared_ptr<Course::TileBase>> m_tiles;
    std::vector<std::shared_ptr<Player>> m_players;
    std::vector<std::shared_ptr<Course::PlaceableGameObject>> m_placeableObjects;
};

} // namespace Game

#endif // OBJECTMANAGER_H
