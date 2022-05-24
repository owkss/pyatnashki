#include "board.h"
#include "functions.h"
#include "dynamiccell.h"
#include "cell.h"

#include <cmath>
#include <random>
#include <cassert>
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

void Board::cell_clicked(DynamicCell *dc)
{
    if (valid_move(dc->current_row(), dc->current_column()))
    {
        int r_tmp = dc->current_row();
        int c_tmp = dc->current_column();
        dc->set_new_position(m_row_empty, m_column_empty);

        m_row_empty = r_tmp;
        m_column_empty = c_tmp;

        update();
        check_win();
    }
}

void Board::generate()
{
    m_static_cells.resize(row_count() * column_count());

    for (int i = 0; i < row_count(); ++i)
    {
        for (int j = 0; j < column_count(); ++j)
        {
            Cell *c = new Cell(i, j, this);
            m_static_cells.push_back(c);
        }
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::vector<int> indexes(row_count() * column_count());
    std::iota(indexes.begin(), indexes.end(), 1);
    std::shuffle(indexes.begin(), indexes.end(), g);

    int r = 0;
    int c = 0;
    for (size_t i = 0; i < indexes.size() - 1; ++i)
    {
        int index = indexes.at(i);
        pyatnashki::position(r, c, index, column_count());

        DynamicCell *dc = new DynamicCell(0, 0, r, c, this);
        connect(dc, &DynamicCell::cell_clicked, this, &Board::cell_clicked);
        m_dynamic_cells.push_back(dc);
    }

    pyatnashki::position(r, c, indexes.back(), column_count());
    m_row_empty = r;
    m_column_empty = c;
}

bool Board::valid_move(int r, int c)
{
    if ((r == m_row_empty - 1 && m_column_empty == c) ||
        (r == m_row_empty + 1 && m_column_empty == c) ||
        (r == m_row_empty && m_column_empty == c - 1) ||
        (r == m_row_empty && m_column_empty == c + 1))
        return true;
    return false;
}

void Board::check_win()
{
    for (int i = 0; i < m_dynamic_cells.size(); ++i)
    {
        DynamicCell *dc = m_dynamic_cells.at(i);
        if (dc->row() != dc->current_row() || dc->column() != dc->current_column())
            return;
    }

    emit win();
}
