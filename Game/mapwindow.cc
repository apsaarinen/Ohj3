#include "mapwindow.hh"
#include "ui_mapwindow.h"

#include "graphics/simplemapitem.h"

#include <math.h>

MapWindow::MapWindow(QWidget *parent,
                     std::shared_ptr<GameEventHandler> handler,
                     std::shared_ptr<ObjectManager> objMan):
    QMainWindow(parent),
    m_ui(new Ui::MapWindow),
    m_GEHandler(handler),
    m_objMan(objMan),
    m_simplescene(new Course::SimpleGameScene(this))
{
    m_ui->setupUi(this);

    Course::SimpleGameScene* sgs_rawptr = m_simplescene.get();
    m_ui->graphicsView->setScene(dynamic_cast<QGraphicsScene*>(sgs_rawptr));
}

MapWindow::~MapWindow()
{
    delete m_ui;
}

void MapWindow::setGEHandler(
        std::shared_ptr<GameEventHandler> nHandler)
{
    m_GEHandler = nHandler;
}

std::shared_ptr<GameEventHandler> MapWindow::getGEHandler()
{
    return m_GEHandler;
}

void MapWindow::setObjMan(std::shared_ptr<ObjectManager> nObjMan)
{
    m_objMan = nObjMan;
}

std::shared_ptr<ObjectManager> MapWindow::getObjMan()
{
    return m_objMan;
}

void MapWindow::setSize(int width, int height)
{
    m_simplescene->setSize(width, height);
}

void MapWindow::setScale(int scale)
{
    m_simplescene->setScale(scale);
}

void MapWindow::resize()
{
    m_simplescene->resize();
}

void MapWindow::updateItem(std::shared_ptr<Course::GameObject> obj)
{
    m_simplescene->updateItem(obj);
}

void MapWindow::changeTurn(const std::shared_ptr<Player> player)
{
    // Update the UI for the current player
}

void MapWindow::removeItem(std::shared_ptr<Course::GameObject> obj)
{
    m_simplescene->removeItem(obj);
}

void MapWindow::drawItem(std::shared_ptr<Course::GameObject> obj)
{
    m_simplescene->drawItem(obj);
}

void MapWindow::on_endTurnButton_clicked()
{
    std::shared_ptr<GameEventHandler> GEHand = getGEHandler();
    std::shared_ptr<ObjectManager> objMan = getObjMan();
    std::vector<std::shared_ptr<Player>> players = objMan->getPlayers();
    std::shared_ptr<Player> playerInTurn = GEHand->getPlayerInTurn();
    // If last player, check for win condition
    if(objMan->isLastPlayer(playerInTurn)) {
        std::vector<std::shared_ptr<Player>> winners = GEHand->checkWinCondition(players);
        if(winners.size() > 0) {
            // Game has ended
            // Show results and exit
        }
    }
    // Give turn to next player
    for(std::shared_ptr<Player> player: players) {
        if(player != playerInTurn) {
            QString playerName = "Player in turn: " + QString::fromStdString(player->getName());
            m_ui->playerNameLabel->setText(playerName);
            GEHand->setPlayerInTurn(player);
            changeTurn(player);
        }
    }
}
