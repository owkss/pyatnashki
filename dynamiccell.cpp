#include "dynamiccell.h"
#include "functions.h"
#include "board.h"

#include <QDebug>
#include <QPainter>

DynamicCell::DynamicCell(const int r, const int c, int current_row, int current_col, Board *parent)
    : Cell(r, c, parent)
    , m_current_row(current_row)
    , m_current_col(current_col)
{
    setZValue(2);
}

QRectF DynamicCell::boundingRect() const
{
    return QRectF(pyatnashki::topleft(current_row(), current_column(), section()), QSizeF(section(), section()));
}

void DynamicCell::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->save();
    painter->fillRect(boundingRect(), QColor(255, 0, 0, 50));
    painter->restore();
}

int DynamicCell::current_row() const noexcept
{
    return m_current_row;
}

int DynamicCell::current_column() const noexcept
{
    return m_current_col;
}

int DynamicCell::current_index() const noexcept
{
    return current_row() * board()->column_count() + current_column() + 1;
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
    emit cell_clicked(this);
}

QVariant DynamicCell::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    return Cell::itemChange(change, value);
}

void DynamicCell::set_new_position(int r, int c)
{
    m_current_row = r;
    m_current_col = c;
    update();
}
