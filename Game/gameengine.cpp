#include "gameengine.h"

GameEngine::GameEngine()
{

}

void GameEngine::setupGame(MapWindow *mapWindow)
{
    auto& worldGen = Course::WorldGenerator::getInstance();
    worldGen.addConstructor<Course::Forest>(10);
    worldGen.addConstructor<Course::Grassland>(1);
//    std::shared_ptr<Course::iObjectManager> objMan = mapWindow->getObjMan();
//    std::shared_ptr<Course::iGameEventHandler> eventHand = mapWindow->getGEHandler();
    std::shared_ptr<Course::SimpleGameScene> sgs = mapWindow->getSGS();

    ObjectManager objMan;
    std::shared_ptr<ObjectManager> objManPtr = std::make_shared<ObjectManager>(objMan);
    GameEventHandler eventHand;
    std::shared_ptr<GameEventHandler> eventHandPtr = std::make_shared<GameEventHandler>(eventHand);

    unsigned int x = 10;
    unsigned int y = 10;
    unsigned int seed = 5;
    worldGen.generateMap(x, y, seed, objManPtr, eventHandPtr);
    std::vector<std::shared_ptr<Course::TileBase>> asd = objManPtr->getTiles();
    for(auto t: asd){
        sgs->drawItem(t);
    }
}
