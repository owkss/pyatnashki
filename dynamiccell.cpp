#include "dynamiccell.h"
#include "board.h"

#include <QDebug>
#include <QPainter>

DynamicCell::DynamicCell(int r, int c, Board *parent)
    : Cell(r, c, parent)
{
    setZValue(2);
}

QRectF DynamicCell::boundingRect() const
{
    return Cell::boundingRect();
}

void DynamicCell::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->save();
    painter->fillRect(boundingRect(), Qt::red);
    painter->restore();
}

void DynamicCell::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsObject::mousePressEvent(event);
}

void DynamicCell::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsObject::mouseMoveEvent(event);
}

void DynamicCell::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsObject::mouseReleaseEvent(event);
}

QVariant DynamicCell::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    switch (change)
    {
    case QGraphicsItem::ItemSelectedChange:
        if (!is_movable())
            return false;
        if (value.toBool())
            emit selection_changed(row(), column());
        else
            emit selection_changed(-1, -1);
        break;
    default:
        break;
    }

    return Cell::itemChange(change, value);
}
