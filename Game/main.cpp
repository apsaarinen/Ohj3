#include "mapwindow.hh"
#include "begindialog.hh"

#include <QApplication>
#include "gameengine.h"

int main(int argc, char* argv[])
{

    QApplication app(argc, argv);

    std::shared_ptr<ObjectManager> objManPtr = std::make_shared<ObjectManager>();
    std::shared_ptr<GameEventHandler> eventHandPtr = std::make_shared<GameEventHandler>();

    begindialog beginDialog;
    beginDialog.show();
    if(beginDialog.exec() == QDialog::Accepted){
        std::vector<std::string> playernames = beginDialog.getPlayernames();
        Course::ResourceMap startingResources = beginDialog.getStartingResources();
        int resources_to_win = beginDialog.getResourcesToWin();
    }
    else{
        exit(0);
    }
    MapWindow mapWindow;
    mapWindow.show();

    GameEngine gameEng;
    gameEng.setupGame(&mapWindow, objManPtr, eventHandPtr);
    //gameEng.turnManager(&mapWindow, objManPtr); // TODO: finish and uncomment

    return app.exec();


}
