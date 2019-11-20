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

void MapWindow::deactivateButtons()
{
    m_ui->button_basicworker->setEnabled(false);
    m_ui->button_endTurn->setEnabled(false);
    m_ui->button_farm->setEnabled(false);
    m_ui->button_getMoney->setEnabled(false);
    m_ui->button_headquarters->setEnabled(false);
    m_ui->button_loseMoney->setEnabled(false);
    m_ui->button_miner->setEnabled(false);
    m_ui->button_mines->setEnabled(false);
    m_ui->button_outpost->setEnabled(false);
    m_ui->button_sawmill->setEnabled(false);
    m_ui->button_sawmillworker->setEnabled(false);
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

void MapWindow::on_button_farm_clicked()
{
    std::shared_ptr<GameEventHandler> GEHand = getGEHandler();
    std::shared_ptr<Player> player = GEHand->getPlayerInTurn();

    m_ui->button_getMoney->setEnabled(false);
    setButtonTooltips();
    m_ui->label_status->setText("Choose a square you want to build this building on.");

    // Player clicks on a square and it's ID is returned

    // Testivaiheeseen mitä tahansa klikkaamalla vain napit takaisin aktiivisiksi jne.
    // Voiko tässä käyttää jotenkin SimpleGameScenen mouseevent kakkaa?
    //if(m_ui->graphicsView->event(QEvent *event)){
    //    m_ui->label_status->setText("Square clicked.");
    //}

    // Check if the square is available
        // If yes, take resources, make object of the building with square ID,
        // make the player owner of the square and put building to players objects.
        // Draw building on the map

        // If no, show error message and continue the turn

}

void MapWindow::on_button_headquarters_clicked()
{
    deactivateButtons();
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
