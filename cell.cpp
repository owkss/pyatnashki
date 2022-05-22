#include "cell.h"
#include "board.h"
#include "functions.h"

#include <QDebug>
#include <QPainter>

Cell::Cell(int r, int c, Board *parent)
    : QGraphicsObject(parent)
    , m_board(parent)
    , m_row(r)
    , m_col(c)
{
    setZValue(1);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setAcceptedMouseButtons(Qt::LeftButton);
}

QRectF Cell::boundingRect() const
{
    return QRectF(tag::topleft(index(), side()), QSizeF(side(), side()));
}

void Cell::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->save();
    painter->drawText(boundingRect(), Qt::AlignCenter, QString::number(index()));
    painter->restore();
}

int Cell::row() const noexcept
{
    return m_row;
}

int Cell::column() const noexcept
{
    return m_col;
}

int Cell::index() const noexcept
{
    return row() * 4 + column();
}

int Cell::side() const noexcept
{
    return m_side;
}

bool Cell::is_movable() const noexcept
{
    const int r = m_board->row_empty();
    const int c = m_board->col_empty();
    if ((row() == r - 1 && column() == c) ||
        (row() == r + 1 && column() == c) ||
        (row() == r && column() == c - 1) ||
        (row() == r && column() == c + 1))
        return true;
    return false;
}

void Cell::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsObject::mousePressEvent(event);
}

void Cell::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsObject::mouseMoveEvent(event);
}

void Cell::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsObject::mouseReleaseEvent(event);
}

void Cell::set_side(int s) noexcept
{
    if (s <= 0)
        return;

    prepareGeometryChange();
    m_side = s;
}
