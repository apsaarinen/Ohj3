#include "mapwindow.hh"

#include <QApplication>
#include "gameengine.h"

int main(int argc, char* argv[])
{

    QApplication app(argc, argv);

    MapWindow mapWindow;
    GameEngine gameEng;
    gameEng.setupGame();



    mapWindow.show();
    return app.exec();


}
