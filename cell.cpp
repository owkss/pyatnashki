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
    return QRectF(pyatnashki::topleft(index(), section(), board()->row_count(), board()->column_count()), QSizeF(section(), section()));
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
    return row() * board()->column_count() + column() + 1;
}

int Cell::section() const noexcept
{
    return m_section;
}

bool Cell::is_movable() const noexcept
{
    const int r = 1; // TODO
    const int c = 1;
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

void Cell::set_section(int s) noexcept
{
    if (s <= 0)
        return;

    prepareGeometryChange();
    m_section = s;
}
