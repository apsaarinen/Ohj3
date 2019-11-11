#include "mapwindow.hh"

#include <QApplication>
#include "gameengine.h"

int main(int argc, char* argv[])
{

    QApplication app(argc, argv);

    std::shared_ptr<ObjectManager> objManPtr = std::make_shared<ObjectManager>();
    std::shared_ptr<GameEventHandler> eventHandPtr = std::make_shared<GameEventHandler>();
    MapWindow mapWindow;
    mapWindow.show();

    GameEngine gameEng;
    gameEng.setupGame(&mapWindow, objManPtr, eventHandPtr);
    //gameEng.turnManager(&mapWindow, objManPtr); // TODO: finish and uncomment

    return app.exec();


}
