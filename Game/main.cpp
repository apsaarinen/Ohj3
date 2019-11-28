#include <QApplication>

#include "ui/mapwindow.hh"
#include "ui/begindialog.hh"
#include "setupgame.h"

int main(int argc, char* argv[])
{

    QApplication app(argc, argv);

    std::shared_ptr<Game::ObjectManager> objManPtr = std::make_shared<
            Game::ObjectManager>();
    std::shared_ptr<Game::GameEventHandler> eventHandPtr = std::make_shared<
            Game::GameEventHandler>();

    // Open a dialog window and ask for initial value for game setup
    begindialog beginDialog;
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
    Game::setupGame(&mapWindow, playernames, startingResources, objManPtr);

    // Start the game by giving the turn to the first player
    mapWindow.changeTurn(eventHandPtr->getPlayerInTurn());

    return app.exec();
}
