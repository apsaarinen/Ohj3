#include "mapwindow.hh"
#include "ui_mapwindow.h"

#include "graphics/simplemapitem.h"

#include <math.h>

MapWindow::MapWindow(QWidget *parent,
                     std::shared_ptr<Course::iGameEventHandler> handler,
                     std::shared_ptr<Course::iObjectManager> manager):
    QMainWindow(parent),
    m_ui(new Ui::MapWindow),
    m_GEHandler(handler),
    m_ObjMan(manager),
    m_simplescene(new Course::SimpleGameScene(this))
{
    m_ui->setupUi(this);

    Course::SimpleGameScene* sgs_rawptr = m_simplescene.get();
//    sgs_rawptr->setSceneRect(10, 10, 100, 100);
    m_ui->graphicsView->setScene(dynamic_cast<QGraphicsScene*>(sgs_rawptr));
//    m_ui->graphicsView->setAlignment(Qt::AlignTop|Qt::AlignLeft);
}

MapWindow::~MapWindow()
{
    delete m_ui;
}

void MapWindow::setGEHandler(
        std::shared_ptr<Course::iGameEventHandler> nHandler)
{
    m_GEHandler = nHandler;
}

void MapWindow::setObjMan(std::shared_ptr<Course::iObjectManager> nManager)
{
    m_ObjMan = nManager;
}

void MapWindow::setSGS(std::shared_ptr<Course::SimpleGameScene> nScene)
{
    m_simplescene = nScene;
}

std::shared_ptr<Course::iGameEventHandler> MapWindow::getGEHandler()
{
    return m_GEHandler;
}

std::shared_ptr<Course::iObjectManager> MapWindow::getObjMan()
{
    return m_ObjMan;
}

std::shared_ptr<Course::SimpleGameScene> MapWindow::getSGS()
{
    return m_simplescene;
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

void MapWindow::removeItem(std::shared_ptr<Course::GameObject> obj)
{
    m_simplescene->removeItem(obj);
}

void MapWindow::drawItem( std::shared_ptr<Course::GameObject> obj)
{
    m_simplescene->drawItem(obj);
}
