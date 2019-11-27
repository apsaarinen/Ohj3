#ifndef MAPWINDOW_HH
#define MAPWINDOW_HH

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

#include <map>

#include "interfaces/igameeventhandler.h"
#include "graphics/gamescene.h"
#include "gameeventhandler.h"
#include "objectmanager.h"
#include "enddialog.hh"
#include "buildings/farm.h"
#include "buildings/headquarters.h"
#include "buildings/outpost.h"
#include "buildings/mine.hh"
#include "buildings/sawmill.hh"
#include "workers/mineworker.h"
#include "workers/sawmillworker.h"
#include "workers/basicworker.h"


namespace Ui {
class MapWindow;
}
/**
 * @brief The MapWindow class is the main game window.
 *
 * The UI consists of the game map, buttons for buying objects and \n
 * information related to the game state.
 */
class MapWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for the class.
     *
     * @param parent can be used to point to a parent widget. Not used.
     * @param GEHandler points to the GameEventHandler
     * @param objMan points to the ObjectManager
     */
    explicit MapWindow(QWidget *parent = 0,
                       std::shared_ptr<GameEventHandler> GEHandler = {},
                       std::shared_ptr<ObjectManager> objMan = {});

    /**
     * @brief Constructor for the class.
     */
    ~MapWindow();

    /**
     * @brief Gets a pointer to the GameEventHandler
     * @return Pointer to the GameEventHandler
     */
    std::shared_ptr<GameEventHandler> getGEHandler();

    /**
     * @brief Gets a pointer to the ObjectManager
     * @return Pointer to the ObjectManager
     */
    std::shared_ptr<ObjectManager> getObjMan();

    /**
     * @brief Sets the game map
     * @param width of the map
     * @param height of the map
     */
    void setSize(int width, int height);

    /**
     * @brief Sets the game map tile scale
     * @param scale of the tiles
     */
    void setScale(int scale);

    /**
     * @brief Recreates the game map base according to the saved dimensions
     */
    void resize();

    /**
     * @brief Draws a GameObject on the game map
     * @param obj object to be drawn
     * @param offset of the object in coordinates
     * @note Offset is used when drawing smaller object in different spots inside tiles.
     */
    void drawItem( std::shared_ptr<Course::GameObject> obj, int offset=0);

    /**
     * @brief Remove a GameObject from the game map
     * @param obj object to be removed
     */
    void removeItem( std::shared_ptr<Course::GameObject> obj);

    /**
     * @brief Updates a GameObject on the game map
     * @param obj object to be updated
     * @note The objects location, shape and color are all updated if needed.
     */
    void updateItem( std::shared_ptr<Course::GameObject> obj);

    /**
     * @brief Changes the UI for the next player in turn
     * @param player pointer to a Player object whose turn it's going to be
     */
    void changeTurn(const std::shared_ptr<Player> player);

    /**
     * @brief Sets up certain fixed elements in the UI when a game is started
     * @param resourcesToWin Amount of resources needed to win the game
     */
    void setupUI(int resourcesToWin);

public slots:
    /**
     * @brief Sets a PlaceableGameObject onto a tile and sets \n
     * owners for required objects
     * @param tileID of the tile clicked
     * @note Executed when a tile is clicked on the map
     */
    void placeObject(Course::ObjectId tileID);

    /**
     * @brief Shows and hides info text of building and hiring buttons when \n
     *  hovered over with mouse.
     * @param watched Objects of buttons that are being tracked for mouse hovering.
     * @param event Enter or leave events when mouse hovering over a button.
     * @return Event to parent class
     */
    bool eventFilter(QObject *watched, QEvent *event);

private slots:
    /**
     * @brief Ends player turn, calculates resources, checks win condition \n
     * and gives the turn to the other player.
     * @note Executed when the button "End turn" is clicked
     */
    void on_button_endTurn_clicked();

    /**
     * @brief Creates a Farm object to a player
     * @note Executed when the button "Build Farm" is clicked
     */
    void on_button_farm_clicked();

    /**
     * @brief Creates a HeadQuarters object to a player
     * @note Executed when the button "Build HQ" is clicked
     */
    void on_button_headquarters_clicked();

    /**
     * @brief Creates a Outpost object to a player
     * @note Executed when the button "Build Outpost" is clicked
     */
    void on_button_outpost_clicked();

    /**
     * @brief Creates a Mine object to a player
     * @note Executed when the button "Build Mine" is clicked
     */
    void on_button_mine_clicked();

    /**
     * @brief Creates a Sawmill object to a player
     * @note Executed when the button "Build Sawmill" is clicked
     */
    void on_button_sawmill_clicked();

    /**
     * @brief Creates a BasicWorker object to a player
     * @note Executed when the button "Hire Basic Worker" is clicked
     */
    void on_button_basicworker_clicked();

    /**
     * @brief Creates a Miner object to a player
     * @note Executed when the button "Hire Miner" is clicked
     */
    void on_button_miner_clicked();

    /**
     * @brief Creates a SawmillWorker object to a player
     * @note Executed when the button "Hire Sawmill Worker" is clicked
     */
    void on_button_sawmillworker_clicked();

private:
    /**
     * @brief Toggles if buttons are enabled in the window
     * @param isActive Boolean value for buttons enabled
     * @note Is used to force a player to click a tile to advance
     */
    void toggleActiveButtons(bool isActive);

    /**
     * @brief Saves an object to a player and enables the \n
     * isPlayerBuying flag
     * @param objMan Pointer to the ObjectManager
     * @param GEHand Pointer to the GameEventHandler
     * @param player Pointer to the player to is buying
     * @param object Pointer to the object that has been bought
     * @note Is called by all Build/Hire button slots to \n
     * combine functionality to one function
     */
    void buyObject(std::shared_ptr<ObjectManager> objMan,
                   std::shared_ptr<GameEventHandler> GEHand,
                   std::shared_ptr<Player> player,
                   std::shared_ptr<Course::PlaceableGameObject> object);

    /**
     * @brief Draws a players resources to the UI
     * @param player Pointer to the player whose resources are drawn
     */
    void drawResources(std::shared_ptr<Player> player);

    /**
     * @brief Ends the game with a window pop-up
     * @param winners Players that have won \n
     * (1player=winner, 2players=draw)
     * @note Game exits in this function and closes all windows
     */
    void endGame(std::vector<std::shared_ptr<Player>> winners);

    Ui::MapWindow* m_ui;
    std::shared_ptr<GameEventHandler> m_GEHandler = nullptr;
    std::shared_ptr<ObjectManager> m_objMan = nullptr;
    std::shared_ptr<GameScene> m_gamescene = nullptr;

};

#endif // MapWINDOW_HH

