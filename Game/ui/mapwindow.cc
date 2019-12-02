#include "mapwindow.hh"
#include "ui_mapwindow.h"

#include "graphics/mapitem.h"

#include <math.h>

MapWindow::MapWindow(QWidget *parent,
                     std::shared_ptr<Game::GameEventHandler> handler,
                     std::shared_ptr<Game::ObjectManager> objMan):
    QMainWindow(parent),
    m_ui(new Ui::MapWindow),
    m_GEHandler(handler),
    m_objMan(objMan),
    m_gamescene(new Game::GameScene(this))
{
    m_ui->setupUi(this);

    Game::GameScene* sgs_rawptr = m_gamescene.get();
    m_ui->graphicsView->setScene(dynamic_cast<QGraphicsScene*>(sgs_rawptr));

    connect(sgs_rawptr, SIGNAL(mapItemClicked(Course::ObjectId)), this, SLOT(placeObject(Course::ObjectId)));

    // Installing event filters for buttons
    m_ui->button_farm->installEventFilter(this);
    m_ui->button_headquarters->installEventFilter(this);
    m_ui->button_outpost->installEventFilter(this);
    m_ui->button_mine->installEventFilter(this);
    m_ui->button_sawmill->installEventFilter(this);
    m_ui->button_basicworker->installEventFilter(this);
    m_ui->button_miner->installEventFilter(this);
    m_ui->button_sawmillworker->installEventFilter(this);

}

MapWindow::~MapWindow()
{
    delete m_ui;
}

std::shared_ptr<Game::GameEventHandler> MapWindow::getGEHandler()
{
    return m_GEHandler;
}

std::shared_ptr<Game::ObjectManager> MapWindow::getObjMan()
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

void MapWindow::changeTurn(const std::shared_ptr<Game::Player> player)
{
    // Set player name in UI
    QString playerName = "Player in turn: " + QString::fromStdString(player->getName());
    m_ui->label_playerName->setText(playerName);
    QString status = QString::fromStdString(player->getName()) + "'s turn.";
    m_ui->label_status->setText(status);

    // Set player resources in UI
    drawResources(player);
}

void MapWindow::setupUI(int resourcesToWin)
{
    m_ui->label_toWin->setText(QString::number(resourcesToWin));
}

void MapWindow::toggleActiveButtons(bool isActive)
{
    m_ui->button_basicworker->setEnabled(isActive);
    m_ui->button_endTurn->setEnabled(isActive);
    m_ui->button_farm->setEnabled(isActive);
    m_ui->button_headquarters->setEnabled(isActive);
    m_ui->button_miner->setEnabled(isActive);
    m_ui->button_mine->setEnabled(isActive);
    m_ui->button_outpost->setEnabled(isActive);
    m_ui->button_sawmill->setEnabled(isActive);
    m_ui->button_sawmillworker->setEnabled(isActive);
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
    else if(watched == (QObject*)m_ui->button_mine){
        if(event->type() == QEvent::Enter){
            m_ui->label_info->show();
            m_ui->label_info->setText(QString("Building a mine costs: \n "
                                              "Money: ") + QString::number(
                                          Game::ConstResourceMaps::MINE_BUILD_COST.at(
                                          Course::BasicResource::MONEY)) + "\n Food: " +
                                          QString::number(Game::ConstResourceMaps::
                                          MINE_BUILD_COST.at(Course::BasicResource::FOOD)) +
                                          "\n Wood: " + QString::number(
                                          Game::ConstResourceMaps::MINE_BUILD_COST.at(
                                          Course::BasicResource::WOOD)) + "\n\nProduction\n "
                                          "Money: " + QString::number(
                                          Game::ConstResourceMaps::MINE_PRODUCTION.at(
                                          Course::BasicResource::MONEY)) + "\n Stone: " +
                                          QString::number(Game::ConstResourceMaps::
                                          MINE_PRODUCTION.at(Course::BasicResource::STONE)) +
                                          "\n Ore: " + QString::number(
                                          Game::ConstResourceMaps::MINE_PRODUCTION.at(
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
                                            Game::ConstResourceMaps::SAWMILL_BUILD_COST.at(
                                            Course::BasicResource::MONEY)) + "\n Food: " +
                                            QString::number(Game::ConstResourceMaps::
                                            SAWMILL_BUILD_COST.at(Course::BasicResource::FOOD)) +
                                            "\n Wood: " + QString::number(
                                            Game::ConstResourceMaps::SAWMILL_BUILD_COST.at(
                                            Course::BasicResource::WOOD)) + "\n\nProduction\n "
                                            "Money: " + QString::number(
                                            Game::ConstResourceMaps::SAWMILL_PRODUCTION.at(
                                            Course::BasicResource::MONEY)) + "\n Food: " +
                                            QString::number(Game::ConstResourceMaps::
                                            SAWMILL_PRODUCTION.at(Course::BasicResource::FOOD)) +
                                            "\n Wood: " + QString::number(
                                            Game::ConstResourceMaps::SAWMILL_PRODUCTION.at(
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
                                            "\n\nWorking efficiency: \n "
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
                                            "\n\nWage per turn\n Money: -1 \n Food: -1");
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
                                            Game::ConstResourceMaps::MW_RECRUITMENT_COST.at(
                                            Course::BasicResource::MONEY)) + "\n Food: " +
                                            QString::number(Game::ConstResourceMaps::
                                            MW_RECRUITMENT_COST.at(Course::BasicResource::FOOD)) +
                                            "\n\nWorking efficiency: \n "
                                            "Money: " + QString::number(
                                            Game::ConstResourceMaps::MW_WORKER_EFFICIENCY.at(
                                            Course::BasicResource::MONEY)) +
                                            "\n Food: " + QString::number(
                                            Game::ConstResourceMaps::MW_WORKER_EFFICIENCY.at(
                                            Course::BasicResource::FOOD)) +
                                            "\n Wood: " + QString::number(
                                            Game::ConstResourceMaps::MW_WORKER_EFFICIENCY.at(
                                            Course::BasicResource::WOOD)) +
                                            "\n Stone: " + QString::number(
                                            Game::ConstResourceMaps::MW_WORKER_EFFICIENCY.at(
                                            Course::BasicResource::STONE)) +
                                            "\n Ore: " + QString::number(
                                            Game::ConstResourceMaps::MW_WORKER_EFFICIENCY.at(
                                            Course::BasicResource::ORE)) +
                                            "\n\nWage per turn\n Money: -2 \n Food: -2");
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
                                            Game::ConstResourceMaps::SMW_RECRUITMENT_COST.at(
                                            Course::BasicResource::MONEY)) + "\n Food: " +
                                            QString::number(Game::ConstResourceMaps::
                                            SMW_RECRUITMENT_COST.at(Course::BasicResource::FOOD)) +
                                            "\n\nWorking efficiency: \n "
                                            "Money: " + QString::number(
                                            Game::ConstResourceMaps::SMW_WORKER_EFFICIENCY.at(
                                            Course::BasicResource::MONEY)) +
                                            "\n Food: " + QString::number(
                                            Game::ConstResourceMaps::SMW_WORKER_EFFICIENCY.at(
                                            Course::BasicResource::FOOD)) +
                                            "\n Wood: " + QString::number(
                                            Game::ConstResourceMaps::SMW_WORKER_EFFICIENCY.at(
                                            Course::BasicResource::WOOD)) +
                                            "\n Stone: " + QString::number(
                                            Game::ConstResourceMaps::SMW_WORKER_EFFICIENCY.at(
                                            Course::BasicResource::STONE)) +
                                            "\n Ore: " + QString::number(
                                            Game::ConstResourceMaps::SMW_WORKER_EFFICIENCY.at(
                                            Course::BasicResource::ORE)) +
                                            "\n\nWage per turn\n Money: -2 \n Food: -2");
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

void MapWindow::drawItem(std::shared_ptr<Course::GameObject> obj, int offset)
{
    m_gamescene->drawItem(obj, offset);
}

void MapWindow::on_button_endTurn_clicked()
{
    std::shared_ptr<Game::GameEventHandler> GEHand = getGEHandler();
    std::shared_ptr<Game::ObjectManager> objMan = getObjMan();
    std::vector<std::shared_ptr<Game::Player>> players = objMan->getPlayers();
    std::shared_ptr<Game::Player> playerInTurn = GEHand->getPlayerInTurn();

    // If last player, check for win condition
    if(objMan->isLastPlayer(playerInTurn)) {
        // Calculate resources
        std::vector<std::shared_ptr<Course::TileBase>> tiles = objMan->getTiles();
        for(std::shared_ptr<Course::TileBase>& tile: tiles) {
            tile->generateResources();
        }
        std::vector<std::shared_ptr<Game::Player>> winners = GEHand->checkWinCondition(players);
        if(winners.size() > 0) {
            // Game has ended
            endGame(winners);
            return;
        }
        m_ui->label_rounds->setText("Round: " + QString::number(GEHand->increaseRounds()));
    }

    // Give turn to next player
    for(std::shared_ptr<Game::Player> player: players) {
        if(player != playerInTurn) {
            GEHand->setPlayerInTurn(player);
            changeTurn(player);
        }
    }
}

void MapWindow::buyObject(std::shared_ptr<Game::ObjectManager> objMan,
                          std::shared_ptr<Game::GameEventHandler> GEHand,
                          std::shared_ptr<Game::Player> player,
                          std::shared_ptr<Course::PlaceableGameObject> object)
{
    // Set buying flag on
    GEHand->setBuyingFlag(true);

    // Deactivate buttons and show help text
    toggleActiveButtons(false);
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
    std::shared_ptr<Game::ObjectManager> objMan = getObjMan();
    std::shared_ptr<Game::GameEventHandler> GEHand = getGEHandler();
    std::shared_ptr<Game::Player> player = GEHand->getPlayerInTurn();

    if(not GEHand->isPlayerBuying()) {
        // Player has not paid or selected a resource to place on the map
        return;
    }

    std::shared_ptr<Course::PlaceableGameObject> object = objMan->getNewestPlaceableObject();

    std::shared_ptr<Course::TileBase> tile = objMan->getTile(tileID);

    if(tile->getOwner() == nullptr or tile->getOwner() == player) {
        if((object->getDescription("type") == "building" and tile->hasSpaceForBuildings(1)) or
                (object->getDescription("type") == "worker" and tile->hasSpaceForWorkers(1))) {

            // Set tile owner
            tile->setOwner(player);

            if(object->getDescription("type") == "building") {
                std::shared_ptr<Course::BuildingBase> objectBuilding = std::static_pointer_cast<Course::BuildingBase>(object);

                object->setCoordinate(tile->getCoordinate());
                // Perform buildings on-build action
                objectBuilding->onBuildAction();
                // Draw object on map
                drawItem(object, tile->getBuildingCount());

                tile->addBuilding(objectBuilding);
                m_ui->label_status->setText("Building placed! Continue your turn.");
            }
            if(object->getDescription("type") == "worker") {

                object->setCoordinate(tile->getCoordinate());
                // Draw object on map
                drawItem(object, tile->getWorkerCount());

                tile->addWorker(std::static_pointer_cast<Course::WorkerBase>(object));
                m_ui->label_status->setText("Worker hired! Continue your turn.");
            }

            // Update map to show drawn building or worker
            m_ui->graphicsView->viewport()->update();

            qDebug() << "Draw building/worker on map!";
            // Disable all buttons again
            toggleActiveButtons(true);

            // Set buying flag off
            GEHand->setBuyingFlag(false);
        }
        else if(tile->getType() == "Water") {
            m_ui->label_status->setText("Objects can't be placed in water! Select another tile.");
        }
        else {
            m_ui->label_status->setText("No space on the tile! Select another one.");
        }
    }
    else {
        m_ui->label_status->setText("Another player owns that tile! Select another one.");
    }
}

void MapWindow::drawResources(std::shared_ptr<Game::Player> player)
{
    Course::ResourceMap playerResources = player->getResources();
    m_ui->label_moneyInput->setText(QString::number(playerResources[Course::BasicResource::MONEY]));
    m_ui->label_foodInput->setText(QString::number(playerResources[Course::BasicResource::FOOD]));
    m_ui->label_woodInput->setText(QString::number(playerResources[Course::BasicResource::WOOD]));
    m_ui->label_stoneInput->setText(QString::number(playerResources[Course::BasicResource::STONE]));
    m_ui->label_oreInput->setText(QString::number(playerResources[Course::BasicResource::ORE]));
    int resourceSum = 0;
    for(auto res: playerResources) {
        resourceSum += res.second;
    }
    m_ui->label_sumInput->setText(QString::number(resourceSum));
}


void MapWindow::endGame(std::vector<std::shared_ptr<Game::Player> > winners)
{
    m_ui->button_endTurn->hide();

    std::shared_ptr<Game::GameEventHandler> GEHand = getGEHandler();
    enddialog endDialog;
    endDialog.setWinner(winners, GEHand->getRounds());
    endDialog.exec();
    qApp->quit();

}

void MapWindow::on_button_farm_clicked()
{
    std::shared_ptr<Game::ObjectManager> objMan = getObjMan();
    std::shared_ptr<Game::GameEventHandler> GEHand = getGEHandler();
    std::shared_ptr<Game::Player> player = GEHand->getPlayerInTurn();
    std::shared_ptr<Course::Farm> selectedObj = std::make_shared<Course::Farm>(GEHand,
                                                                               objMan,
                                                                               player);
    selectedObj->addDescription("type", "building");
    // Create a negative version of the BUILD_COST resource map
    Course::ResourceMap cost = Course::multiplyResourceMap(Course::ConstResourceMaps::FARM_BUILD_COST,
                                                           Game::ConstResourceMaps::NEGATIVE);
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
    std::shared_ptr<Game::ObjectManager> objMan = getObjMan();
    std::shared_ptr<Game::GameEventHandler> GEHand = getGEHandler();
    std::shared_ptr<Game::Player> player = GEHand->getPlayerInTurn();
    std::shared_ptr<Course::HeadQuarters> selectedObj = std::make_shared<Course::HeadQuarters>(GEHand,
                                                                                               objMan,
                                                                                               player);
    selectedObj->addDescription("type", "building");
    // Create a negative version of the BUILD_COST resource map
    Course::ResourceMap cost = Course::multiplyResourceMap(Course::ConstResourceMaps::HQ_BUILD_COST,
                                                           Game::ConstResourceMaps::NEGATIVE);
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
    std::shared_ptr<Game::ObjectManager> objMan = getObjMan();
    std::shared_ptr<Game::GameEventHandler> GEHand = getGEHandler();
    std::shared_ptr<Game::Player> player = GEHand->getPlayerInTurn();
    std::shared_ptr<Course::Outpost> selectedObj = std::make_shared<Course::Outpost>(GEHand,
                                                                                     objMan,
                                                                                     player);
    selectedObj->addDescription("type", "building");
    // Create a negative version of the BUILD_COST resource map
    Course::ResourceMap cost = Course::multiplyResourceMap(Course::ConstResourceMaps::OUTPOST_BUILD_COST,
                                                           Game::ConstResourceMaps::NEGATIVE);
    if(player->modifyResources(cost)) {
        // Player had money and paid for the object
        buyObject(objMan, GEHand, player, selectedObj);
    }
    else {
        m_ui->label_status->setText("Not enough resources!");
    }
}

void MapWindow::on_button_mine_clicked()
{
    std::shared_ptr<Game::ObjectManager> objMan = getObjMan();
    std::shared_ptr<Game::GameEventHandler> GEHand = getGEHandler();
    std::shared_ptr<Game::Player> player = GEHand->getPlayerInTurn();
    std::shared_ptr<Game::Mine> selectedObj = std::make_shared<Game::Mine>(GEHand,
                                                               objMan,
                                                               player);
    selectedObj->addDescription("type", "building");
    // Create a negative version of the BUILD_COST resource map
    Course::ResourceMap cost = Course::multiplyResourceMap(Game::ConstResourceMaps::MINE_BUILD_COST,
                                                           Game::ConstResourceMaps::NEGATIVE);
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
    std::shared_ptr<Game::ObjectManager> objMan = getObjMan();
    std::shared_ptr<Game::GameEventHandler> GEHand = getGEHandler();
    std::shared_ptr<Game::Player> player = GEHand->getPlayerInTurn();
    std::shared_ptr<Game::SawMill> selectedObj = std::make_shared<Game::SawMill>(GEHand,
                                                                     objMan,
                                                                     player);
    selectedObj->addDescription("type", "building");
    // Create a negative version of the BUILD_COST resource map
    Course::ResourceMap cost = Course::multiplyResourceMap(Game::ConstResourceMaps::SAWMILL_BUILD_COST,
                                                           Game::ConstResourceMaps::NEGATIVE);
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
    std::shared_ptr<Game::ObjectManager> objMan = getObjMan();
    std::shared_ptr<Game::GameEventHandler> GEHand = getGEHandler();
    std::shared_ptr<Game::Player> player = GEHand->getPlayerInTurn();
    std::shared_ptr<Course::BasicWorker> selectedObj = std::make_shared<Course::BasicWorker>(GEHand,
                                                                                             objMan,
                                                                                             player);
    selectedObj->addDescription("type", "worker");
    // Create a negative version of the BUILD_COST resource map
    Course::ResourceMap cost = Course::multiplyResourceMap(Course::ConstResourceMaps::BW_RECRUITMENT_COST,
                                                           Game::ConstResourceMaps::NEGATIVE);
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
    std::shared_ptr<Game::ObjectManager> objMan = getObjMan();
    std::shared_ptr<Game::GameEventHandler> GEHand = getGEHandler();
    std::shared_ptr<Game::Player> player = GEHand->getPlayerInTurn();
    std::shared_ptr<Game::MineWorker> selectedObj = std::make_shared<Game::MineWorker>(GEHand,
                                                                           objMan,
                                                                           player);
    selectedObj->addDescription("type", "worker");
    // Create a negative version of the BUILD_COST resource map
    Course::ResourceMap cost = Course::multiplyResourceMap(Game::ConstResourceMaps::MW_RECRUITMENT_COST,
                                                           Game::ConstResourceMaps::NEGATIVE);
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
    std::shared_ptr<Game::ObjectManager> objMan = getObjMan();
    std::shared_ptr<Game::GameEventHandler> GEHand = getGEHandler();
    std::shared_ptr<Game::Player> player = GEHand->getPlayerInTurn();
    std::shared_ptr<Game::SawMillWorker> selectedObj = std::make_shared<Game::SawMillWorker>(GEHand,
                                                                                 objMan,
                                                                                 player);
    selectedObj->addDescription("type", "worker");
    // Create a negative version of the BUILD_COST resource map
    Course::ResourceMap cost = Course::multiplyResourceMap(Game::ConstResourceMaps::SMW_RECRUITMENT_COST,
                                                           Game::ConstResourceMaps::NEGATIVE);
    if(player->modifyResources(cost)) {
        // Player had money and paid for the object
        buyObject(objMan, GEHand, player, selectedObj);
    }
    else {
        m_ui->label_status->setText("Not enough resources!");
    }
}
