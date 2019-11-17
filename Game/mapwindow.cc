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

    // Set player name in UI
    QString playerName = "Player in turn: " + QString::fromStdString(player->getName());
    m_ui->label_playerName->setText(playerName);

    // Set player resources in UI
    drawResources(player);

    // Highlight or color tiles?
}

void MapWindow::removeItem(std::shared_ptr<Course::GameObject> obj)
{
    m_simplescene->removeItem(obj);
}

void MapWindow::drawItem(std::shared_ptr<Course::GameObject> obj)
{
    m_simplescene->drawItem(obj);
}

void MapWindow::on_button_endTurn_clicked()
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
            endGame(winners);
            return;
        }
    }
    // Give turn to next player
    for(std::shared_ptr<Player> player: players) {
        if(player != playerInTurn) {
            GEHand->setPlayerInTurn(player);
            changeTurn(player);
        }
    }
}

void MapWindow::on_button_getMoney_clicked()
{
    std::shared_ptr<GameEventHandler> GEHand = getGEHandler();
    std::shared_ptr<Player> player = GEHand->getPlayerInTurn();
    GEHand->newModifyResource(player, Course::BasicResource::MONEY, 100);
    drawResources(player);
}

void MapWindow::on_button_loseMoney_clicked()
{
    std::shared_ptr<GameEventHandler> GEHand = getGEHandler();
    std::shared_ptr<Player> player = GEHand->getPlayerInTurn();
    GEHand->newModifyResource(player, Course::BasicResource::MONEY, -100);
    drawResources(player);
}

void MapWindow::drawResources(std::shared_ptr<Player> player)
{
    Course::ResourceMap playerResources = player->getResources();
    m_ui->label_moneyInput->setText(QString::number(playerResources[Course::BasicResource::MONEY]));
    m_ui->label_foodInput->setText(QString::number(playerResources[Course::BasicResource::FOOD]));
    m_ui->label_woodInput->setText(QString::number(playerResources[Course::BasicResource::WOOD]));
    m_ui->label_stoneInput->setText(QString::number(playerResources[Course::BasicResource::STONE]));
    m_ui->label_oreInput->setText(QString::number(playerResources[Course::BasicResource::ORE]));
    int resourceSum;
    for(auto res: playerResources) {
        resourceSum += res.second;
    }
    m_ui->label_sumInput->setText(QString::number(resourceSum));
}

// TODO: this could lauch a pop-up that closes the game?
void MapWindow::endGame(std::vector<std::shared_ptr<Player> > winners)
{
    if(winners.size() == 1) {
        // One winner
        QString winnerText = "Player " +
                QString::fromStdString(winners[0]->getName()) +
                " has won the game!";
        m_ui->label_playerName->setText(winnerText);
    } else {
        // Draw
        m_ui->label_playerName->setText("It's a draw!");
    }
    m_ui->button_endTurn->hide();
}
