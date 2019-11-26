#include "mapwindow.hh"
#include "begindialog.hh"

#include <QApplication>
#include "setupgame.h"

int main(int argc, char* argv[])
{

    QApplication app(argc, argv);

    std::shared_ptr<ObjectManager> objManPtr = std::make_shared<ObjectManager>();
    std::shared_ptr<GameEventHandler> eventHandPtr = std::make_shared<GameEventHandler>();

    // Open a dialog window and ask for initial value for game setup
    begindialog beginDialog;
    // Pressed "Cancel" or shut down the window
    if(beginDialog.exec() != QDialog::Accepted){
        return 0;
    }
    // Getting the initial values from the begindialog
    std::vector<std::string> playernames = beginDialog.getPlayernames();
    Course::ResourceMap startingResources = beginDialog.getStartingResources();
    int resourcesToWin = beginDialog.getResourcesToWin();
    eventHandPtr->setResourcesToWin(resourcesToWin);

    MapWindow mapWindow(0, eventHandPtr, objManPtr);
    mapWindow.setScale(75);
    mapWindow.showFullScreen();

    mapWindow.setupUI(resourcesToWin);
    setupGame(&mapWindow, playernames, startingResources, objManPtr);

    // Start the game by giving the turn to the first player
    mapWindow.changeTurn(eventHandPtr->getPlayerInTurn());

    return app.exec();
}
