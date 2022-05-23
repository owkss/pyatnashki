#include "board.h"
#include "functions.h"
#include "dynamiccell.h"
#include "cell.h"

#include <cmath>
#include <iostream>

#include <QDebug>
#include <QPainter>

Board::Board(int r, int c, QGraphicsItem *parent)
    : QGraphicsObject(parent)
{
    setFlags(QGraphicsItem::ItemSendsGeometryChanges);

    if (r > 0)
        m_rows = r;
    if (c > 0)
        m_columns = c;

    generate();
}

QRectF Board::boundingRect() const
{
    return QRectF(0, 0, width(), height());
}

void Board::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->save();

    QPen pen = painter->pen();
    pen.setWidth(pyatnashki::MARGIN / 2);
    painter->setPen(pen);

    int count = m_rows * m_columns;
    for(int i = 0; i < count; ++i)
    {
        painter->drawRect(QRectF(pyatnashki::topleft(i + 1, section(), row_count(), column_count()), QSizeF(section(), section())));
    }

    painter->restore();
}

int Board::width() const noexcept
{
    return section() * column_count() + pyatnashki::MARGIN * column_count() - 1;
}

int Board::height() const noexcept
{
    return section() * row_count() + pyatnashki::MARGIN * row_count() - 1;
}

int Board::section() const noexcept
{
    return m_section;
}

void Board::recalc_size(const QSize &sz) noexcept
{
    prepareGeometryChange();

    const int w = sz.width() / column_count();
    const int h = sz.height() / row_count();
    m_section = std::min(w, h) - pyatnashki::MARGIN;

    QList<QGraphicsItem*> items = childItems();
    for (int i = 0; i < items.size(); ++i)
    {
        if (Cell *c = qgraphicsitem_cast<Cell*>(items.at(i)))
        {
            c->set_section(section());
        }
    }
}

void Board::generate()
{
    m_static_cells.resize(row_count());
    for (auto &c : m_static_cells) c.resize(column_count());

    for (int i = 0; i < row_count(); ++i)
    {
        for (int j = 0; j < column_count(); ++j)
        {
            m_static_cells[i][j] = new Cell(i, j, this);
        }
    }
}
