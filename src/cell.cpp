#include "cell.h"
#include "functions.h"
#include "board.h"

#include <QDebug>
#include <QPainter>

Cell::Cell(const QImage &img, const int r, const int c, int current_row, int current_col, Board *parent)
    : QGraphicsObject(parent)
    , m_row(r)
    , m_col(c)
    , m_current_row(current_row)
    , m_current_col(current_col)
    , m_image(img)
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
    return QRectF(pyatnashki::topleft(current_row(), current_column(), section()), QSizeF(section(), section()));
}

void Cell::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->save();
    if (m_image.isNull())
        painter->drawText(boundingRect(), Qt::AlignCenter, QString::number(index()));
    else
        painter->drawImage(boundingRect(), m_image);
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

int Cell::current_row() const noexcept
{
    return m_current_row;
}

int Cell::current_column() const noexcept
{
    return m_current_col;
}

int Cell::current_index() const noexcept
{
    return current_row() * board()->count() + current_column() + 1;
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
    emit cell_clicked(this);
}

QVariant Cell::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    return QGraphicsObject::itemChange(change, value);
}

void Cell::set_section(int s) noexcept
{
    if (s <= 0)
        return;

    prepareGeometryChange();
    m_section = s;
}

void Cell::set_new_position(int r, int c)
{
    m_current_row = r;
    m_current_col = c;
    update();
}
