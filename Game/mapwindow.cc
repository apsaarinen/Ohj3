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

    // Installing event filters for buttons
    m_ui->button_farm->installEventFilter(this);
    m_ui->button_headquarters->installEventFilter(this);
    m_ui->button_outpost->installEventFilter(this);
    m_ui->button_mines->installEventFilter(this);
    m_ui->button_sawmill->installEventFilter(this);
    m_ui->button_basicworker->installEventFilter(this);
    m_ui->button_miner->installEventFilter(this);
    m_ui->button_sawmillworker->installEventFilter(this);

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
    QString status = QString::fromStdString(player->getName()) + "'s turn.";
    m_ui->label_status->setText(status);

    // Set player resources in UI
    drawResources(player);

    // Highlight or color tiles?
}

void MapWindow::toggleActiveButtons(bool isActive)
{
    m_ui->button_basicworker->setEnabled(isActive);
    m_ui->button_endTurn->setEnabled(isActive);
    m_ui->button_farm->setEnabled(isActive);
    m_ui->button_getMoney->setEnabled(isActive);
    m_ui->button_headquarters->setEnabled(isActive);
    m_ui->button_loseMoney->setEnabled(isActive);
    m_ui->button_miner->setEnabled(isActive);
    m_ui->button_mines->setEnabled(isActive);
    m_ui->button_outpost->setEnabled(isActive);
    m_ui->button_sawmill->setEnabled(isActive);
    m_ui->button_sawmillworker->setEnabled(isActive);
}

void MapWindow::setButtonTooltips()
{
    m_ui->button_farm->setToolTip(QString("Money: ") + QString::number(
                                      Course::ConstResourceMaps::FARM_BUILD_COST.at(
                                          Course::BasicResource::MONEY)));
}

bool MapWindow::eventFilter(QObject *watched, QEvent *event)
{
    // Farm
    if(watched == (QObject*)m_ui->button_farm){
        if(event->type() == QEvent::Enter){
            m_ui->label_info->show();
            m_ui->label_info->setText(QString("Building a farm costs: \n "
                                              "Money: ") + QString::number(
                                            Course::ConstResourceMaps::FARM_BUILD_COST.at(
                                            Course::BasicResource::MONEY)) + "\n Food: " +
                                            QString::number(Course::ConstResourceMaps::
                                            FARM_BUILD_COST.at(Course::BasicResource::FOOD)) +
                                            "\n Wood: " + QString::number(
                                            Course::ConstResourceMaps::FARM_BUILD_COST.at(
                                            Course::BasicResource::WOOD))+
                                            "\n\nProduction\n " "Money: " + QString::number(
                                            Course::ConstResourceMaps::FARM_PRODUCTION.at(
                                            Course::BasicResource::MONEY)) + "\n Food: " +
                                            QString::number(Course::ConstResourceMaps::
                                            FARM_PRODUCTION.at(Course::BasicResource::FOOD)));
        }
        else if(event->type() == QEvent::Leave){
            m_ui->label_info->hide();
        }
        return QWidget::eventFilter(watched,event);
    }

    // Headquarters
    else if(watched == (QObject*)m_ui->button_headquarters){
        if(event->type() == QEvent::Enter){
            m_ui->label_info->show();
            m_ui->label_info->setText(QString("Building an HQ costs: \n "
                                              "Money: ") + QString::number(
                                            Course::ConstResourceMaps::HQ_BUILD_COST.at(
                                            Course::BasicResource::MONEY)) + "\n Food: " +
                                            QString::number(Course::ConstResourceMaps::
                                            HQ_BUILD_COST.at(Course::BasicResource::FOOD)) +
                                            "\n Wood: " + QString::number(
                                            Course::ConstResourceMaps::HQ_BUILD_COST.at(
                                            Course::BasicResource::WOOD)) + "\n Stone: " +
                                            QString::number(Course::ConstResourceMaps::
                                            HQ_BUILD_COST.at(Course::BasicResource::STONE)) +
                                            "\n\nProduction\n " "Money: " + QString::number(
                                            Course::ConstResourceMaps::HQ_PRODUCTION.at(
                                            Course::BasicResource::MONEY)) + "\n Food: " +
                                            QString::number(Course::ConstResourceMaps::
                                            HQ_PRODUCTION.at(Course::BasicResource::FOOD)));
        }
        else if(event->type() == QEvent::Leave){
            m_ui->label_info->hide();
        }
        return QWidget::eventFilter(watched,event);
    }

    // Outpost
    else if(watched == (QObject*)m_ui->button_outpost){
        if(event->type() == QEvent::Enter){
            m_ui->label_info->show();
            m_ui->label_info->setText(QString("Building an outpost costs: \n "
                                              "Money: ") + QString::number(
                                          Course::ConstResourceMaps::OUTPOST_BUILD_COST.at(
                                          Course::BasicResource::MONEY)) + "\n Food: " +
                                          QString::number(Course::ConstResourceMaps::
                                          OUTPOST_BUILD_COST.at(Course::BasicResource::FOOD)) +
                                          "\n Wood: " + QString::number(
                                          Course::ConstResourceMaps::OUTPOST_BUILD_COST.at(
                                          Course::BasicResource::WOOD)) +
                                          "\n Stone: " + QString::number(
                                          Course::ConstResourceMaps::OUTPOST_BUILD_COST.at(
                                          Course::BasicResource::STONE)) + "\n\nProduction\n "
                                          "Money: " + QString::number(
                                          Course::ConstResourceMaps::OUTPOST_PRODUCTION.at(
                                          Course::BasicResource::MONEY)) + "\n Food: " +
                                          QString::number(Course::ConstResourceMaps::
                                          OUTPOST_PRODUCTION.at(Course::BasicResource::FOOD)));
        }

        else if(event->type() == QEvent::Leave){
            m_ui->label_info->hide();
        }
        return QWidget::eventFilter(watched,event);
    }

    // Mines
    else if(watched == (QObject*)m_ui->button_mines){
        if(event->type() == QEvent::Enter){
            m_ui->label_info->show();
            m_ui->label_info->setText(QString("Building a mine costs: \n "
                                              "Money: ") + QString::number(
                                          Course::ConstResourceMaps::MINE_BUILD_COST.at(
                                          Course::BasicResource::MONEY)) + "\n Food: " +
                                          QString::number(Course::ConstResourceMaps::
                                          MINE_BUILD_COST.at(Course::BasicResource::FOOD)) +
                                          "\n Wood: " + QString::number(
                                          Course::ConstResourceMaps::MINE_BUILD_COST.at(
                                          Course::BasicResource::WOOD)) + "\n\nProduction\n "
                                          "Money: " + QString::number(
                                          Course::ConstResourceMaps::MINE_PRODUCTION.at(
                                          Course::BasicResource::MONEY)) + "\n Stone: " +
                                          QString::number(Course::ConstResourceMaps::
                                          MINE_PRODUCTION.at(Course::BasicResource::STONE)) +
                                          "\n Ore: " + QString::number(
                                          Course::ConstResourceMaps::MINE_PRODUCTION.at(
                                          Course::BasicResource::ORE)));
        }
        else if(event->type() == QEvent::Leave){
            m_ui->label_info->hide();
        }
        return QWidget::eventFilter(watched,event);
    }

    // Sawmill
    else if(watched == (QObject*)m_ui->button_sawmill){
        if(event->type() == QEvent::Enter){
            m_ui->label_info->show();
            m_ui->label_info->setText(QString("Building a sawmill costs: \n "
                                              "Money: ") + QString::number(
                                            Course::ConstResourceMaps::SAWMILL_BUILD_COST.at(
                                            Course::BasicResource::MONEY)) + "\n Food: " +
                                            QString::number(Course::ConstResourceMaps::
                                            SAWMILL_BUILD_COST.at(Course::BasicResource::FOOD)) +
                                            "\n Wood: " + QString::number(
                                            Course::ConstResourceMaps::SAWMILL_BUILD_COST.at(
                                            Course::BasicResource::WOOD)) + "\n\nProduction\n "
                                            "Money: " + QString::number(
                                            Course::ConstResourceMaps::SAWMILL_PRODUCTION.at(
                                            Course::BasicResource::MONEY)) + "\n Food: " +
                                            QString::number(Course::ConstResourceMaps::
                                            SAWMILL_PRODUCTION.at(Course::BasicResource::FOOD)) +
                                            "\n Wood: " + QString::number(
                                            Course::ConstResourceMaps::SAWMILL_PRODUCTION.at(
                                            Course::BasicResource::WOOD)));
        }
        else if(event->type() == QEvent::Leave){
            m_ui->label_info->hide();
        }
        return QWidget::eventFilter(watched,event);
    }

    // Basic Worker
    else if(watched == (QObject*)m_ui->button_basicworker){
        if(event->type() == QEvent::Enter){
            m_ui->label_info->show();
            m_ui->label_info->setText(QString("Hiring a basic worker costs: \n "
                                              "Money: ") + QString::number(
                                            Course::ConstResourceMaps::BW_RECRUITMENT_COST.at(
                                            Course::BasicResource::MONEY)) + "\n Food: " +
                                            QString::number(Course::ConstResourceMaps::
                                            BW_RECRUITMENT_COST.at(Course::BasicResource::FOOD)) +
                                            "\n\n Working efficiency: \n"
                                            "Money: " + QString::number(
                                            Course::ConstResourceMaps::BW_WORKER_EFFICIENCY.at(
                                            Course::BasicResource::MONEY)) +
                                            "\n Food: " + QString::number(
                                            Course::ConstResourceMaps::BW_WORKER_EFFICIENCY.at(
                                            Course::BasicResource::FOOD)) +
                                            "\n Wood: " + QString::number(
                                            Course::ConstResourceMaps::BW_WORKER_EFFICIENCY.at(
                                            Course::BasicResource::WOOD)) +
                                            "\n Stone: " + QString::number(
                                            Course::ConstResourceMaps::BW_WORKER_EFFICIENCY.at(
                                            Course::BasicResource::STONE)) +
                                            "\n Ore: " + QString::number(
                                            Course::ConstResourceMaps::BW_WORKER_EFFICIENCY.at(
                                            Course::BasicResource::ORE)) +
                                            "\n\n Wage per turn\n Money: -1 \n Food: -1");
        }
        else if(event->type() == QEvent::Leave){
            m_ui->label_info->hide();
        }
        return QWidget::eventFilter(watched,event);
    }

    // Miner
    else if(watched == (QObject*)m_ui->button_miner){
        if(event->type() == QEvent::Enter){
            m_ui->label_info->show();
            m_ui->label_info->setText(QString("Hiring a miner costs: \n "
                                              "Money: ") + QString::number(
                                            Course::ConstResourceMaps::MW_RECRUITMENT_COST.at(
                                            Course::BasicResource::MONEY)) + "\n Food: " +
                                            QString::number(Course::ConstResourceMaps::
                                            MW_RECRUITMENT_COST.at(Course::BasicResource::FOOD)) +
                                            "\n\n Working efficiency: \n"
                                            "Money: " + QString::number(
                                            Course::ConstResourceMaps::MW_WORKER_EFFICIENCY.at(
                                            Course::BasicResource::MONEY)) +
                                            "\n Food: " + QString::number(
                                            Course::ConstResourceMaps::MW_WORKER_EFFICIENCY.at(
                                            Course::BasicResource::FOOD)) +
                                            "\n Wood: " + QString::number(
                                            Course::ConstResourceMaps::MW_WORKER_EFFICIENCY.at(
                                            Course::BasicResource::WOOD)) +
                                            "\n Stone: " + QString::number(
                                            Course::ConstResourceMaps::MW_WORKER_EFFICIENCY.at(
                                            Course::BasicResource::STONE)) +
                                            "\n Ore: " + QString::number(
                                            Course::ConstResourceMaps::MW_WORKER_EFFICIENCY.at(
                                            Course::BasicResource::ORE)) +
                                            "\n\n Wage per turn\n Money: -2 \n Food: -2");
        }
        else if(event->type() == QEvent::Leave){
            m_ui->label_info->hide();
        }
        return QWidget::eventFilter(watched,event);
    }

    // Sawmill worker
    else if(watched == (QObject*)m_ui->button_sawmillworker){
        if(event->type() == QEvent::Enter){
            m_ui->label_info->show();
            m_ui->label_info->setText(QString("Hiring a sawmill worker costs: \n "
                                              "Money: ") + QString::number(
                                            Course::ConstResourceMaps::SMW_RECRUITMENT_COST.at(
                                            Course::BasicResource::MONEY)) + "\n Food: " +
                                            QString::number(Course::ConstResourceMaps::
                                            SMW_RECRUITMENT_COST.at(Course::BasicResource::FOOD)) +
                                            "\n\n Working efficiency: \n"
                                            "Money: " + QString::number(
                                            Course::ConstResourceMaps::SMW_WORKER_EFFICIENCY.at(
                                            Course::BasicResource::MONEY)) +
                                            "\n Food: " + QString::number(
                                            Course::ConstResourceMaps::SMW_WORKER_EFFICIENCY.at(
                                            Course::BasicResource::FOOD)) +
                                            "\n Wood: " + QString::number(
                                            Course::ConstResourceMaps::SMW_WORKER_EFFICIENCY.at(
                                            Course::BasicResource::WOOD)) +
                                            "\n Stone: " + QString::number(
                                            Course::ConstResourceMaps::SMW_WORKER_EFFICIENCY.at(
                                            Course::BasicResource::STONE)) +
                                            "\n Ore: " + QString::number(
                                            Course::ConstResourceMaps::SMW_WORKER_EFFICIENCY.at(
                                            Course::BasicResource::ORE)) +
                                            "\n\n Wage per turn\n Money: -2 \n Food: -2");
        }
        else if(event->type() == QEvent::Leave){
            m_ui->label_info->hide();
        }
        return QWidget::eventFilter(watched,event);
    }
    else{
        return QWidget::eventFilter(watched,event);
    }
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
        // Calculate resources
        std::vector<std::shared_ptr<Course::TileBase>> tiles = objMan->getTiles();
        for(std::shared_ptr<Course::TileBase>& tile: tiles) {
            tile->generateResources();
        }
    }

    // Give turn to next player
    for(std::shared_ptr<Player> player: players) {
        // TODO: Järkevämpi toteutus tähän(?)
        if(objMan->isLastPlayer(playerInTurn)){

        }
        else{
            std::vector<std::shared_ptr<Player>> winners = GEHand->checkWinCondition(players);
            if(winners.size() > 0) {
                // Chance to draw for player last in turn
                m_ui->label_chancetodraw->setText(QString::fromStdString(players[0]->getName()) +
                                                " is winning, " +QString::fromStdString(
                                                players[1]->getName()) + " has a chance to draw!");
            }
        }

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

void MapWindow::buyObject(std::shared_ptr<ObjectManager> objMan, std::shared_ptr<GameEventHandler> GEHand, std::shared_ptr<Player> player, std::shared_ptr<Course::PlaceableGameObject> object)
{
    // Set buying flag on
    GEHand->setBuyingFlag(true);

    // Deactivate buttons and maybe show help text
    toggleActiveButtons(false);
    setButtonTooltips();
    if(object->getDescription("type") == "building") {
        m_ui->label_status->setText("Choose a square you want to build the building on.");
    }
    if(object->getDescription("type") == "worker") {
        m_ui->label_status->setText("Choose a square you want to hire the worker on.");
    }

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

            if(object->getDescription("type") == "building") {
                tile->addBuilding(std::static_pointer_cast<Course::BuildingBase>(object));
                m_ui->label_status->setText("Building placed!");
            }
            if(object->getDescription("type") == "worker") {
                tile->addWorker(std::static_pointer_cast<Course::WorkerBase>(object));
                m_ui->label_status->setText("Worker hired!");
            }

            // TODO: draw object on the map
            drawItem(object);

            qDebug() << "Draw building/worker on map!";
            // Disable all buttons again
            toggleActiveButtons(true);

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

void MapWindow::on_button_headquarters_clicked()
{
    std::shared_ptr<ObjectManager> objMan = getObjMan();
    std::shared_ptr<GameEventHandler> GEHand = getGEHandler();
    std::shared_ptr<Player> player = GEHand->getPlayerInTurn();
    std::shared_ptr<Course::HeadQuarters> selectedObj = std::make_shared<Course::HeadQuarters>(GEHand,
                                                                                       objMan,
                                                                                       player);
    selectedObj->addDescription("type", "building");
    // Create a negative version of the BUILD_COST resource map
    Course::ResourceMap cost = Course::multiplyResourceMap(Course::ConstResourceMaps::HQ_BUILD_COST, Course::ConstResourceMaps::NEGATIVE);
    if(player->modifyResources(cost)) {
        // Player had money and paid for the object
        buyObject(objMan, GEHand, player, selectedObj);
    }
    else {
        m_ui->label_status->setText("Not enough resources!");
    }
}

void MapWindow::on_button_outpost_clicked()
{
    std::shared_ptr<ObjectManager> objMan = getObjMan();
    std::shared_ptr<GameEventHandler> GEHand = getGEHandler();
    std::shared_ptr<Player> player = GEHand->getPlayerInTurn();
    std::shared_ptr<Course::Outpost> selectedObj = std::make_shared<Course::Outpost>(GEHand,
                                                                                       objMan,
                                                                                       player);
    selectedObj->addDescription("type", "building");
    // Create a negative version of the BUILD_COST resource map
    Course::ResourceMap cost = Course::multiplyResourceMap(Course::ConstResourceMaps::OUTPOST_BUILD_COST, Course::ConstResourceMaps::NEGATIVE);
    if(player->modifyResources(cost)) {
        // Player had money and paid for the object
        buyObject(objMan, GEHand, player, selectedObj);
    }
    else {
        m_ui->label_status->setText("Not enough resources!");
    }
}

void MapWindow::on_button_mines_clicked()
{
    std::shared_ptr<ObjectManager> objMan = getObjMan();
    std::shared_ptr<GameEventHandler> GEHand = getGEHandler();
    std::shared_ptr<Player> player = GEHand->getPlayerInTurn();
    std::shared_ptr<Mine> selectedObj = std::make_shared<Mine>(GEHand,
                                                                                       objMan,
                                                                                       player);
    selectedObj->addDescription("type", "building");
    // Create a negative version of the BUILD_COST resource map
    Course::ResourceMap cost = Course::multiplyResourceMap(Course::ConstResourceMaps::MINE_BUILD_COST, Course::ConstResourceMaps::NEGATIVE);
    if(player->modifyResources(cost)) {
        // Player had money and paid for the object
        buyObject(objMan, GEHand, player, selectedObj);
    }
    else {
        m_ui->label_status->setText("Not enough resources!");
    }
}

void MapWindow::on_button_sawmill_clicked()
{
    std::shared_ptr<ObjectManager> objMan = getObjMan();
    std::shared_ptr<GameEventHandler> GEHand = getGEHandler();
    std::shared_ptr<Player> player = GEHand->getPlayerInTurn();
    std::shared_ptr<SawMill> selectedObj = std::make_shared<SawMill>(GEHand,
                                                                                       objMan,
                                                                                       player);
    selectedObj->addDescription("type", "building");
    // Create a negative version of the BUILD_COST resource map
    Course::ResourceMap cost = Course::multiplyResourceMap(Course::ConstResourceMaps::SAWMILL_BUILD_COST, Course::ConstResourceMaps::NEGATIVE);
    if(player->modifyResources(cost)) {
        // Player had money and paid for the object
        buyObject(objMan, GEHand, player, selectedObj);
    }
    else {
        m_ui->label_status->setText("Not enough resources!");
    }
}

void MapWindow::on_button_basicworker_clicked()
{
    std::shared_ptr<ObjectManager> objMan = getObjMan();
    std::shared_ptr<GameEventHandler> GEHand = getGEHandler();
    std::shared_ptr<Player> player = GEHand->getPlayerInTurn();
    std::shared_ptr<Course::BasicWorker> selectedObj = std::make_shared<Course::BasicWorker>(GEHand,
                                                                                       objMan,
                                                                                       player);
    selectedObj->addDescription("type", "worker");
    // Create a negative version of the BUILD_COST resource map
    Course::ResourceMap cost = Course::multiplyResourceMap(Course::ConstResourceMaps::BW_RECRUITMENT_COST, Course::ConstResourceMaps::NEGATIVE);
    if(player->modifyResources(cost)) {
        // Player had money and paid for the object
        buyObject(objMan, GEHand, player, selectedObj);
    }
    else {
        m_ui->label_status->setText("Not enough resources!");
    }
}

void MapWindow::on_button_miner_clicked()
{
    std::shared_ptr<ObjectManager> objMan = getObjMan();
    std::shared_ptr<GameEventHandler> GEHand = getGEHandler();
    std::shared_ptr<Player> player = GEHand->getPlayerInTurn();
    std::shared_ptr<MineWorker> selectedObj = std::make_shared<MineWorker>(GEHand,
                                                                                       objMan,
                                                                                       player);
    selectedObj->addDescription("type", "worker");
    // Create a negative version of the BUILD_COST resource map
    Course::ResourceMap cost = Course::multiplyResourceMap(Course::ConstResourceMaps::MW_RECRUITMENT_COST, Course::ConstResourceMaps::NEGATIVE);
    if(player->modifyResources(cost)) {
        // Player had money and paid for the object
        buyObject(objMan, GEHand, player, selectedObj);
    }
    else {
        m_ui->label_status->setText("Not enough resources!");
    }
}

void MapWindow::on_button_sawmillworker_clicked()
{
    std::shared_ptr<ObjectManager> objMan = getObjMan();
    std::shared_ptr<GameEventHandler> GEHand = getGEHandler();
    std::shared_ptr<Player> player = GEHand->getPlayerInTurn();
    std::shared_ptr<SawMillWorker> selectedObj = std::make_shared<SawMillWorker>(GEHand,
                                                                                       objMan,
                                                                                       player);
    selectedObj->addDescription("type", "worker");
    // Create a negative version of the BUILD_COST resource map
    Course::ResourceMap cost = Course::multiplyResourceMap(Course::ConstResourceMaps::SMW_RECRUITMENT_COST, Course::ConstResourceMaps::NEGATIVE);
    if(player->modifyResources(cost)) {
        // Player had money and paid for the object
        buyObject(objMan, GEHand, player, selectedObj);
    }
    else {
        m_ui->label_status->setText("Not enough resources!");
    }
}
