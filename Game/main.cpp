#include "mapwindow.hh"

#include <QApplication>
#include "gameengine.h"

int main(int argc, char* argv[])
{

    QApplication app(argc, argv);

    std::shared_ptr<ObjectManager> objManPtr = std::make_shared<ObjectManager>();
    std::shared_ptr<GameEventHandler> eventHandPtr = std::make_shared<GameEventHandler>();

    // Open a dialog window and ask for initial value for game setup
    begindialog beginDialog;
    std::vector<std::string> playernames;
    Course::ResourceMap startingResources;
    // Pressed "OK"
    if(beginDialog.exec() == QDialog::Accepted){
        playernames = beginDialog.getPlayernames();
        startingResources = beginDialog.getStartingResources();
        eventHandPtr->setResourcesToWin(beginDialog.getResourcesToWin());
    }
    // Pressed "Cancel" or shut down the window
    else{
        return 0;
    }

    MapWindow mapWindow;
    mapWindow.setScale(75);
    mapWindow.show();

    GameEngine gameEng;
    mapWindow.setGEHandler(eventHandPtr);
    mapWindow.setObjMan(objManPtr);
    gameEng.setupGame(&mapWindow, playernames, startingResources);
    gameEng.startGame(&mapWindow, objManPtr);

    return app.exec();


}
