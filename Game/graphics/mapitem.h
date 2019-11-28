#ifndef MAPITEM_H
#define MAPITEM_H

#include <QGraphicsItem>
#include <QPainter>

#include <memory>
#include <map>

#include "core/gameobject.h"
#include "core/player.h"
#include "buildings/buildingbase.h"

namespace Game {

using ColorMap = std::map<std::string, QColor>;

const ColorMap MAP_COLORS = {
    {"Blockfield", QColor(192, 192, 192)},
    {"OreDeposit", QColor(64, 64, 64)},
    {"Water", QColor(51, 153, 255)},
    {"Forest", QColor(0, 102, 0)},
    {"Grassland", QColor(128, 255, 0)}
};

/**
 * @brief The MapItem class is a custom QGraphicsItem that
 * acts as a single GameObject's graphical element.
 */
class MapItem : public QGraphicsItem
{
public:
    /**
     * @brief Constructor
     * @param obj shared_ptr to the obj.
     * @param size of the created item in pixels.
     * @param offset for the item in the tile
     * @pre obj must have a valid Coordinate.
     */
    MapItem(const std::shared_ptr<Course::GameObject> &obj,
            int size,
            int offset);

    /**
     * @brief boundingRect
     * @return the bounding rectangle of this item.
     */
    QRectF boundingRect() const override;

    /**
     * @brief Finds the corresponding image for the object
     * @pre object must have an image named accordingly to its
     * object type
     * @return object's image
     * @post Exception guarantee: No-throw
     */
    QPixmap image() const;

    /**
     * @brief paints the item
     * @param painter
     * @param option
     * @param widget
     * @note The GraphicsView containing the scene this belongs to
     * usually calls this function.
     */
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    /**
     * @brief getBoundObject
     * @return the object this item is bound to.
     */
    const std::shared_ptr<Course::GameObject> &getBoundObject();

    /**
     * @brief updateLoc moves the item if the position has changed.
     */
    void updateLoc();

    /**
     * @brief checks if this instance has obj as bound obj.
     * @param obj to compare to.
     * @return True: if obj is pointing to the same object as this item.
     * False otherwise.
     */
    bool isSameObj(std::shared_ptr<Course::GameObject> obj);

private:
    const std::shared_ptr<Course::GameObject> m_gameobject;
    QPoint m_scenelocation;
    int m_size;
    int m_offset;

    static ColorMap c_mapcolors;

};

} // namespace Game

#endif // MAPITEM_H
