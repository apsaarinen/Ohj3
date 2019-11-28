#include "mapitem.h"

namespace Game {

std::map<std::string, QColor> MapItem::c_mapcolors = {};

MapItem::MapItem(const std::shared_ptr<Course::GameObject> &obj, int size, int offset ):
    m_gameobject(obj), m_scenelocation(m_gameobject->getCoordinatePtr()->asQpoint()),
    m_size(size), m_offset(offset)
{
    // Workers and buildings are only 1/3 of the tile's scale
    if(m_gameobject->getDescription("type") == "worker" or
            m_gameobject->getDescription("type") == "building") {
        m_size = m_size/3;
    // If is tile: set its color it accordingly to its type
    } else {
        c_mapcolors.insert({m_gameobject->getType(), MAP_COLORS.at(m_gameobject->getType())});
    }
}

QRectF MapItem::boundingRect() const
{
    // Buildings are drawn on the upper part of the tile
    if(m_gameobject->getDescription("type") == "building") {
        int loc_x = m_scenelocation.x();
        int loc_y = m_scenelocation.y();
        loc_x *= m_size*3;
        loc_x += m_size*m_offset;
        QPoint topLeft = QPoint(loc_x, loc_y*m_size*3);
        return QRectF(topLeft , topLeft + QPoint(m_size, m_size));
    // Workers are drawn on the lower part of the tile
    } else if(m_gameobject->getDescription("type") == "worker") {
        int loc_x = m_scenelocation.x();
        int loc_y = m_scenelocation.y();
        loc_y *= m_size*3;
        loc_x *= m_size*3;
        loc_y += m_size*2;
        loc_x += m_size*m_offset;
        QPoint topLeft = QPoint(loc_x, loc_y);
        return QRectF(topLeft , topLeft + QPoint(m_size, m_size));
    // Tiles are drawn "normally"
    } else {
        return QRectF(m_scenelocation * m_size, m_scenelocation * m_size + QPoint(m_size, m_size));
    }
}

QPixmap MapItem::image() const
{
    QString imagePath = ":/images/" + QString::fromStdString(m_gameobject->getType()) + ".png";
    return QPixmap(imagePath);
}

void MapItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED( option ); Q_UNUSED( widget );
    if (m_gameobject->getDescription("type") == "building" or
            m_gameobject->getDescription("type") == "worker"){

        std::shared_ptr<Player> player = std::static_pointer_cast<Player>(m_gameobject->getOwner());
        painter->setBrush(QBrush(QColor(player->getColor())));
        // Draw the rectangle in the background with player color
        painter->drawRect(boundingRect());
        // Draw an image into the rectangle with original image color
        painter->drawPixmap(boundingRect().toRect(), image());

    } else { // Is tile

        painter->setBrush(QBrush(c_mapcolors.at(m_gameobject->getType())));
        painter->drawRect(boundingRect());

    }
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
        update(boundingRect());
        m_scenelocation = m_gameobject->getCoordinate().asQpoint();
    }
}

bool MapItem::isSameObj(std::shared_ptr<Course::GameObject> obj)
{
    return obj == m_gameobject;
}

} // namespace Game
