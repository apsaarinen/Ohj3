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

// All buildings and workers
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

class MapWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MapWindow(QWidget *parent = 0,
                       std::shared_ptr<GameEventHandler> GEHandler = {},
                       std::shared_ptr<ObjectManager> objMan = {});
    ~MapWindow();

    void setGEHandler(std::shared_ptr<GameEventHandler> nHandler);
    std::shared_ptr<GameEventHandler> getGEHandler();
    void setObjMan(std::shared_ptr<ObjectManager> nObjMan);
    std::shared_ptr<ObjectManager> getObjMan();
//    void setSGS(std::shared_ptr<Course::SimpleGameScene> sgs); TODO: Needed?

    void setSize(int width, int height);
    void setScale(int scale);
    void resize();

    void drawItem( std::shared_ptr<Course::GameObject> obj, int offset);
    void removeItem( std::shared_ptr<Course::GameObject> obj);
    void updateItem( std::shared_ptr<Course::GameObject> obj);

    void changeTurn(const std::shared_ptr<Player> player);

public slots:
    void placeObject(Course::ObjectId tileID);

    void toggleActiveButtons(bool isActive);

    // Varmaan turha
    void setButtonTooltips();

    bool eventFilter(QObject *watched, QEvent *event);

private slots:
    void on_button_endTurn_clicked();

    void on_button_farm_clicked();

    void on_button_headquarters_clicked();

    void on_button_outpost_clicked();

    void on_button_mines_clicked();

    void on_button_sawmill_clicked();

    void on_button_basicworker_clicked();

    void on_button_miner_clicked();

    void on_button_sawmillworker_clicked();

private:
    void buyObject(std::shared_ptr<ObjectManager> objMan, std::shared_ptr<GameEventHandler> GEHand, std::shared_ptr<Player> player, std::shared_ptr<Course::PlaceableGameObject> object);
    void drawResources(std::shared_ptr<Player> player);
    void endGame(std::vector<std::shared_ptr<Player>> winners);

    Ui::MapWindow* m_ui;
    std::shared_ptr<GameEventHandler> m_GEHandler = nullptr;
    std::shared_ptr<ObjectManager> m_objMan = nullptr;
    std::shared_ptr<GameScene> m_gamescene = nullptr;


};

#endif // MapWINDOW_HH

