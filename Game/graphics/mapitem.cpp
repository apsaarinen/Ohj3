#include "mapitem.h"

std::map<std::string, QColor> MapItem::c_mapcolors = {};

MapItem::MapItem(const std::shared_ptr<Course::GameObject> &obj, int size, int offset ):
    m_gameobject(obj), m_scenelocation(m_gameobject->getCoordinatePtr()->asQpoint()),
    m_size(size), m_offset(offset)
{
    addNewColor(m_gameobject->getType()); // TODO is this needed at all?
}

QRectF MapItem::boundingRect() const
{
    return QRectF(m_scenelocation * m_size, m_scenelocation * m_size + QPoint(m_size, m_size));
}

QRectF MapItem::boundingSmallRect() const
{
    std::string gg = m_gameobject->getDescription("type");
    if(m_gameobject->getDescription("type") == "building") {
        int loc_x = m_scenelocation.x();
        int loc_y = m_scenelocation.y();
        loc_x *= m_size*3;
        loc_x += m_size*m_offset;
        QPoint topLeft = QPoint(loc_x, loc_y*m_size*3);
        return QRectF(topLeft , topLeft + QPoint(m_size, m_size));
    } else {
        int loc_x = m_scenelocation.x();
        int loc_y = m_scenelocation.y();
        loc_y *= m_size*3;
        loc_x *= m_size*3;
        loc_y += m_size*2;
        loc_x += m_size*m_offset;
        QPoint topLeft = QPoint(loc_x, loc_y);
        return QRectF(topLeft , topLeft + QPoint(m_size, m_size));
    }
}

QPixmap MapItem::image() const
{
    std::string type = m_gameobject->getType();
    QPixmap pmap;
    bool loaded = pmap.load("/home/kytomaki/programming3/apjajoni/Game/images/hakku.png");
    if(type == "Mine") {
        return QPixmap("/home/kytomaki/programming3/apjajoni/Game/images/hakku.png");
    }

}

void MapItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED( option ); Q_UNUSED( widget );

    if (m_gameobject->getDescription("type") == "building" or m_gameobject->getDescription("type") == "worker"){
        std::shared_ptr<Player> player = std::static_pointer_cast<Player>(m_gameobject->getOwner());
        painter->setBrush(QBrush(player->getColor()));
        // Draw different types in different shapes
//        painter->setBackground(Qt::transparent);
//        painter->setPen(Qt::transparent);
//        painter->setBrush(Qt::transparent);
        painter->drawRect(boundingSmallRect());


        painter->drawPixmap(boundingSmallRect().toRect(), image());

        return;
    }
    painter->setBrush(QBrush(c_mapcolors.at(m_gameobject->getType())));
    painter->drawRect(boundingRect());
}

const std::shared_ptr<Course::GameObject> &MapItem::getBoundObject()
{
    return m_gameobject;
}

void MapItem::updateLoc()
{
    if ( !m_gameobject ){
        delete this;
    } else {
        update(boundingRect()); // Test if necessary
        m_scenelocation = m_gameobject->getCoordinate().asQpoint();
    }
}

bool MapItem::isSameObj(std::shared_ptr<Course::GameObject> obj)
{
    return obj == m_gameobject;
}

int MapItem::getSize() const
{
    return m_size;
}

void MapItem::setSize(int size)
{
    if ( size > 0 && size <= 500 ){
        m_size = size;
    }
}

void MapItem::addNewColor(std::string type)
{
    if ( c_mapcolors.find(type) == c_mapcolors.end() and MAP_COLORS.find(type) != MAP_COLORS.end() ){
        c_mapcolors.insert({type, MAP_COLORS.at(type)});

    }
}

