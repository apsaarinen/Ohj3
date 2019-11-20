#include "mapwindow.hh"
#include "ui_mapwindow.h"

#include "graphics/mapitem.h"

#include <math.h>

MapWindow::MapWindow(QWidget *parent,
                     std::shared_ptr<GameEventHandler> handler,
                     std::shared_ptr<ObjectManager> objMan):
    QMainWindow(parent),
    m_ui(new Ui::MapWindow),
    m_GEHandler(handler),
    m_objMan(objMan),
    m_gamescene(new GameScene(this))
{
    m_ui->setupUi(this);

    GameScene* sgs_rawptr = m_gamescene.get();
    m_ui->graphicsView->setScene(dynamic_cast<QGraphicsScene*>(sgs_rawptr));

    connect(sgs_rawptr, SIGNAL(mapItemClicked(Course::ObjectId)), this, SLOT(placeObject(Course::ObjectId)));
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
    m_gamescene->setSize(width, height);
}

void MapWindow::setScale(int scale)
{
    m_gamescene->setScale(scale);
}

void MapWindow::resize()
{
    m_gamescene->resize();
}

void MapWindow::updateItem(std::shared_ptr<Course::GameObject> obj)
{
    m_gamescene->updateItem(obj);
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
    m_gamescene->removeItem(obj);
}

void MapWindow::drawItem(std::shared_ptr<Course::GameObject> obj)
{
    m_gamescene->drawItem(obj);
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
    GEHand->modifyResource(player, Course::BasicResource::MONEY, 100);
    drawResources(player);
}

void MapWindow::on_button_loseMoney_clicked()
{
    std::shared_ptr<GameEventHandler> GEHand = getGEHandler();
    std::shared_ptr<Player> player = GEHand->getPlayerInTurn();
    GEHand->modifyResource(player, Course::BasicResource::MONEY, -100);
    drawResources(player);
}

void MapWindow::on_button_farm_clicked()
{
    std::shared_ptr<ObjectManager> objMan = getObjMan();
    std::shared_ptr<GameEventHandler> GEHand = getGEHandler();
    std::shared_ptr<Player> player = GEHand->getPlayerInTurn();
    std::shared_ptr<Course::Farm> selectedObj = std::make_shared<Course::Farm>(GEHand,
                                                                               objMan,
                                                                               player);
    selectedObj->addDescription("type", "building");
    // Create a negative version of the BUILD_COST resource map
    Course::ResourceMap cost = Course::multiplyResourceMap(Course::ConstResourceMaps::FARM_BUILD_COST, Course::ConstResourceMaps::NEGATIVE);
    if(player->modifyResources(cost)) {
        // Player had money and paid for the object
        buyObject(objMan, GEHand, player, selectedObj);
    }
    else {
        m_ui->label_status->setText("Not enough resources!");
    }
}

void MapWindow::buyObject(std::shared_ptr<ObjectManager> objMan, std::shared_ptr<GameEventHandler> GEHand, std::shared_ptr<Player> player, std::shared_ptr<Course::PlaceableGameObject> object)
{
    // Set buying flag on
    GEHand->setBuyingFlag(true);

    // Deactivate buttons and maybe show help text
    m_ui->button_getMoney->setEnabled(false);
    m_ui->label_status->setText("Choose a square you want to build this building on.");

    // Save the object to objman and player
    objMan->addPlaceableObject(object);
    player->addObject(object);

    drawResources(player);
}

void MapWindow::placeObject(Course::ObjectId tileID)
{
    std::shared_ptr<ObjectManager> objMan = getObjMan();
    std::shared_ptr<GameEventHandler> GEHand = getGEHandler();
    std::shared_ptr<Player> player = GEHand->getPlayerInTurn();

    if(not GEHand->isPlayerBuying()) {
        // Player has not paid or selected a resource to place on the map
        return;
    }

    std::shared_ptr<Course::PlaceableGameObject> object = objMan->getNewestPlaceableObject();

    std::shared_ptr<Course::TileBase> tile = objMan->getTile(tileID);

    if(tile->getOwner() == nullptr or tile->getOwner() == player) {
        if((object->getDescription("type") == "building" and tile->hasSpaceForBuildings(1)) or
                (object->getDescription("type") == "worker" and tile->hasSpaceForWorkers(1))) {
            // Draw building on map
            object->setCoordinate(tile->getCoordinate());
            // Set tile owner
            tile->setOwner(player);
            // TODO: set owner for adjacent tiles
            qDebug() << "Draw building/worker on map!";
            // Enable all buttons again and maybe change instruction text

            // Set buying flag off
            GEHand->setBuyingFlag(false);
        }
        else {
            m_ui->label_status->setText("No space on the tile! Select another one.");
        }
    }
    else {
        m_ui->label_status->setText("Another player owns that tile! Select another one.");
    }
    // Display error?
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


void MapWindow::endGame(std::vector<std::shared_ptr<Player> > winners)
{
    m_ui->button_endTurn->hide();

    enddialog endDialog;
    endDialog.setWinner(winners);
    if(endDialog.exec() == QDialog::Accepted){
        exit(0);
    }
    else{
        exit(0);
    }




}
