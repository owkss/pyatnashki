#include "board.h"
#include "functions.h"
#include "dynamiccell.h"
#include "cell.h"

#include <QDebug>
#include <QPainter>

Board::Board(QGraphicsItem *parent)
    : QGraphicsObject(parent)
{
    setFlags(QGraphicsItem::ItemSendsGeometryChanges);

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            Cell *c = new Cell(i, j, this);
            m_static_cells[i][j] = c;

            if (!(i == 3 && j == 3))
            {
                DynamicCell *dc = new DynamicCell(i, j, this);
                QObject::connect(dc, &DynamicCell::selection_changed, this, &Board::selection_changed);
                m_cells.push_back(dc);
            }
        }
    }
}

QRectF Board::boundingRect() const
{
    return QRectF(0, 0, side(), side());
}

void Board::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->save();

    QPen pen = painter->pen();
    pen.setWidth(tag::MARGIN / 2);
    painter->setPen(pen);

    for(int i = 0; i < 16; ++i)
    {
        painter->drawRect(QRectF(tag::topleft(i, section()), QSizeF(section(), section())));
    }

    painter->restore();
}

int Board::side() const noexcept
{
    return m_side;
}

int Board::section() const noexcept
{
    return (side() - tag::MARGIN * 3) / 4;
}

void Board::selection_changed(int r, int c)
{
    m_row_select = r;
    m_col_select = c;
}

void Board::cell_clicked(int r, int c)
{
    if (m_row_select == -1 || m_col_select == -1)
        return;

    for (DynamicCell *dc : m_cells)
    {
        if (dc->row() == r && dc->column() == c)
        {
            qDebug() << __PRETTY_FUNCTION__;
        }
    }
}

void Board::set_side(int s) noexcept
{
    if (s <= 0)
        return;

    prepareGeometryChange();
    m_side = s;

    QList<QGraphicsItem*> items = childItems();
    for (int i = 0; i < items.size(); ++i)
    {
        if (Cell *c = qgraphicsitem_cast<Cell*>(items.at(i)))
        {
            c->set_side(section());
        }
    }
}
