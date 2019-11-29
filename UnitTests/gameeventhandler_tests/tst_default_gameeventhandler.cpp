#include <QString>
#include <QtTest>

#include "core/gameeventhandler.h"
#include "core/objectmanager.h"
#include "core/player.h"

using namespace Game;

/**
 * @brief The gameventhandler_tests test the GameEventHandler class
 */
class default_gameeventhandler : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Test setup
     */
    default_gameeventhandler();

private Q_SLOTS:

    /**
     * @brief Tests player reaching the win condition
     * @post Player should be selected as the winner
     */
    void test_playerHasWon();

    /**
     * @brief Tests modifying a player's resource
     * @post Resource should be modified accordingly
     */
    void test_modifyResource();

    /**
     * @brief Tests modifying a player's resources
     * @post Resources should be modified accordingly
     */
    void test_modifyResources();

    /**
     * @brief Tests getting and setting the player in turn
     * @post Player in turn should change and be returned correctly
     */
    void test_playerInTurn();

    /**
     * @brief Tests getting and setting the buying-flag
     * @post Buying flag should change and be returned correctly
     */
    void test_isBuying();

    /**
     * @brief Tests getting and increasing the current game round
     * @post Rounds should increase and be returned correctly
     */
    void test_rounds();


    /**
     * @brief Test cleanup
     */
    void cleanup();

private:
    std::shared_ptr<ObjectManager> objMan;
    std::shared_ptr<GameEventHandler> gameeventhandler_object;

    int winResourceSum;
    Course::ResourceMap zeroResources;
    Course::ResourceMap startResources;
    Course::ResourceMap minusStartResources;

    std::shared_ptr<Player> player1;
    std::shared_ptr<Player> player2;

};

default_gameeventhandler::default_gameeventhandler()
{
    objMan = std::make_shared<ObjectManager>();
    gameeventhandler_object = std::make_shared<GameEventHandler>();
    winResourceSum = 499;

    zeroResources = {
        {Course::BasicResource::MONEY, 0},
        {Course::BasicResource::FOOD, 0},
        {Course::BasicResource::WOOD, 0},
        {Course::BasicResource::STONE, 0},
        {Course::BasicResource::ORE, 0},
    };

    startResources = {
        {Course::BasicResource::MONEY, 100},
        {Course::BasicResource::FOOD, 100},
        {Course::BasicResource::WOOD, 100},
        {Course::BasicResource::STONE, 100},
        {Course::BasicResource::ORE, 100},
    };

    minusStartResources = {
        {Course::BasicResource::MONEY, -100},
        {Course::BasicResource::FOOD, -100},
        {Course::BasicResource::WOOD, -100},
        {Course::BasicResource::STONE, -100},
        {Course::BasicResource::ORE, -100},
    };

    player1 = std::make_shared<Player>("player1", QString("red"));
    player2 = std::make_shared<Player>("player2", QString("blue"));
    objMan->addPlayer(player1);
    objMan->addPlayer(player2);

}

void default_gameeventhandler::test_playerHasWon()
{
    std::vector<std::shared_ptr<Player>> players;
    players.push_back(player1);
    players.push_back(player2);
    gameeventhandler_object->setResourcesToWin(winResourceSum);
    gameeventhandler_object->modifyResources(player1, zeroResources);
    QVERIFY(player1->getResources().at(Course::BasicResource::MONEY) == 0);
    QVERIFY(gameeventhandler_object->checkWinCondition(players).size() == 0);

    gameeventhandler_object->modifyResources(player1, startResources);
    QVERIFY(player1->getResources().at(Course::BasicResource::MONEY) == 100);
    QVERIFY(gameeventhandler_object->checkWinCondition(players).at(0) == player1);
}

void default_gameeventhandler::test_modifyResource()
{
    gameeventhandler_object->modifyResources(player1, zeroResources);
    QVERIFY(player1->getResources().at(Course::BasicResource::MONEY) == 0);
    QVERIFY(player1->getResources().at(Course::BasicResource::FOOD) == 0);
    QVERIFY(player1->getResources().at(Course::BasicResource::WOOD) == 0);
    QVERIFY(player1->getResources().at(Course::BasicResource::STONE) == 0);
    QVERIFY(player1->getResources().at(Course::BasicResource::ORE) == 0);
    gameeventhandler_object->modifyResources(player1, startResources);
    QVERIFY(player1->getResources().at(Course::BasicResource::MONEY) == 100);
    QVERIFY(player1->getResources().at(Course::BasicResource::FOOD) == 100);
    QVERIFY(player1->getResources().at(Course::BasicResource::WOOD) == 100);
    QVERIFY(player1->getResources().at(Course::BasicResource::STONE) == 100);
    QVERIFY(player1->getResources().at(Course::BasicResource::ORE) == 100);
    gameeventhandler_object->modifyResources(player1, minusStartResources);
    QVERIFY(player1->getResources().at(Course::BasicResource::MONEY) == 0);
    QVERIFY(player1->getResources().at(Course::BasicResource::FOOD) == 0);
    QVERIFY(player1->getResources().at(Course::BasicResource::WOOD) == 0);
    QVERIFY(player1->getResources().at(Course::BasicResource::STONE) == 0);
    QVERIFY(player1->getResources().at(Course::BasicResource::ORE) == 0);
    gameeventhandler_object->modifyResources(player1, minusStartResources);
    QVERIFY(player1->getResources().at(Course::BasicResource::MONEY) == 0);
    QVERIFY(player1->getResources().at(Course::BasicResource::FOOD) == 0);
    QVERIFY(player1->getResources().at(Course::BasicResource::WOOD) == 0);
    QVERIFY(player1->getResources().at(Course::BasicResource::STONE) == 0);
    QVERIFY(player1->getResources().at(Course::BasicResource::ORE) == 0);
}

void default_gameeventhandler::test_modifyResources()
{
    gameeventhandler_object->modifyResource(player1, Course::BasicResource::MONEY, 0);
    gameeventhandler_object->modifyResource(player1, Course::BasicResource::FOOD, 0);
    QVERIFY(player1->getResources().at(Course::BasicResource::MONEY) == 0);
    QVERIFY(player1->getResources().at(Course::BasicResource::FOOD) == 0);
    gameeventhandler_object->modifyResource(player1, Course::BasicResource::MONEY, 100);
    QVERIFY(player1->getResources().at(Course::BasicResource::MONEY) == 100);
    QVERIFY(player1->getResources().at(Course::BasicResource::FOOD) == 0);
    gameeventhandler_object->modifyResource(player1, Course::BasicResource::FOOD, -100);
    QVERIFY(player1->getResources().at(Course::BasicResource::FOOD) == 0);
}

void default_gameeventhandler::test_playerInTurn()
{
    QVERIFY(gameeventhandler_object->getPlayerInTurn() == nullptr);
    gameeventhandler_object->setPlayerInTurn(player1);
    QVERIFY(gameeventhandler_object->getPlayerInTurn() == player1);
    gameeventhandler_object->setPlayerInTurn(player2);
    QVERIFY(gameeventhandler_object->getPlayerInTurn() == player2);
}

void default_gameeventhandler::test_isBuying()
{
    QVERIFY(gameeventhandler_object->isPlayerBuying() == false);
    gameeventhandler_object->setBuyingFlag(true);
    QVERIFY(gameeventhandler_object->isPlayerBuying() == true);
}

void default_gameeventhandler::test_rounds()
{
    QVERIFY(gameeventhandler_object->getRounds() == 1);
    QVERIFY(gameeventhandler_object->increaseRounds() == 2);
}


void default_gameeventhandler::cleanup()
{
    objMan = std::make_shared<ObjectManager>();
    gameeventhandler_object = std::make_shared<GameEventHandler>();
    winResourceSum = 499;

    zeroResources = {
        {Course::BasicResource::MONEY, 0},
        {Course::BasicResource::FOOD, 0},
        {Course::BasicResource::WOOD, 0},
        {Course::BasicResource::STONE, 0},
        {Course::BasicResource::ORE, 0},
    };

    startResources = {
        {Course::BasicResource::MONEY, 100},
        {Course::BasicResource::FOOD, 100},
        {Course::BasicResource::WOOD, 100},
        {Course::BasicResource::STONE, 100},
        {Course::BasicResource::ORE, 100},
    };

    minusStartResources = {
        {Course::BasicResource::MONEY, -100},
        {Course::BasicResource::FOOD, -100},
        {Course::BasicResource::WOOD, -100},
        {Course::BasicResource::STONE, -100},
        {Course::BasicResource::ORE, -100},
    };

    player1 = std::make_shared<Player>("player1", QString("red"));
    player2 = std::make_shared<Player>("player2", QString("blue"));
    objMan->addPlayer(player1);
    objMan->addPlayer(player2);

}


QTEST_APPLESS_MAIN(default_gameeventhandler)

#include "tst_default_gameeventhandler.moc"
