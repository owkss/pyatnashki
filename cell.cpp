#include "cell.h"
#include "board.h"
#include "functions.h"

#include <QDebug>
#include <QPainter>

Cell::Cell(const int r, const int c, Board *parent)
    : QGraphicsObject(parent)
    , m_row(r)
    , m_col(c)
{
    setZValue(1);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setAcceptedMouseButtons(Qt::LeftButton);
}

Cell::~Cell()
{

}

QRectF Cell::boundingRect() const
{
    return QRectF(pyatnashki::topleft(index(), section(), board()->count()), QSizeF(section(), section()));
}

void Cell::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->save();
    //painter->drawText(boundingRect(), Qt::AlignCenter, QString::number(index()));
    painter->restore();
}

Board *Cell::board() const noexcept
{
    return qgraphicsitem_cast<Board*>(parentItem());
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
    return row() * board()->count() + column() + 1;
}

int Cell::section() const noexcept
{
    return m_section;
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
