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

    // TODO: Dialog box for game setup

    GameEngine gameEng;
    gameEng.setupGame(&mapWindow, objManPtr, eventHandPtr);


    return app.exec();


}
