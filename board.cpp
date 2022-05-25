#include "board.h"
#include "functions.h"
#include "cell.h"
#include "cell.h"

#include <cmath>
#include <random>
#include <cassert>
#include <iostream>

#include <QDebug>
#include <QMovie>
#include <QPainter>

Board::Board(const QList<QImage> &images, int count, QGraphicsItem *parent)
    : QGraphicsObject(parent)
{
    setFlags(QGraphicsItem::ItemSendsGeometryChanges);

    if (count > 0)
        m_count = count;

    generate(images);
}

QRectF Board::boundingRect() const
{
    return QRectF(0, 0, side(), side());
}

void Board::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->save();

    if (game_over && movie)
    {
        painter->drawImage(boundingRect(), movie->currentImage());
    }
    else
    {
        QPen pen = painter->pen();
        pen.setWidth(pyatnashki::MARGIN / 2);
        pen.setColor(Qt::black);
        painter->setPen(pen);

        for(int i = 0; i < count(); ++i)
        {
            for (int j = 0; j < count(); ++j)
            {
                painter->drawRect(QRectF(pyatnashki::topleft(i, j, section()), QSizeF(section(), section())));
            }
        }
    }

    painter->restore();
}

int Board::side() const noexcept
{
    return section() * count() + pyatnashki::MARGIN * count() - 1;
}

int Board::section() const noexcept
{
    return m_section;
}

void Board::recalc_size(const QSize &sz) noexcept
{
    prepareGeometryChange();

    const int w = sz.width() / count();
    const int h = sz.height() / count();
    m_section = std::min(w, h) - pyatnashki::MARGIN;

    emit set_section(section());
}

void Board::cell_clicked(Cell *dc)
{
    if (!valid_move(dc->current_row(), dc->current_column()))
        return;

    int r_tmp = dc->current_row();
    int c_tmp = dc->current_column();
    dc->set_new_position(m_row_empty, m_column_empty);

    m_row_empty = r_tmp;
    m_column_empty = c_tmp;

    emit step_has_been_taken();

    update();
    check_win();
}

void Board::generate(const QList<QImage> &images)
{
    bool valid_images = true;
    if (images.size() != count() * count())
    {
        valid_images = false;
        std::cerr << "generate(): images.size() != count() * count()" << std::endl;
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::vector<int> indexes(count() * count());
    std::iota(indexes.begin(), indexes.end(), 1);
    //std::shuffle(indexes.begin(), indexes.end(), g);

    int current_row = 0;
    int current_col = 0;
    for (size_t i = 0; i < indexes.size() - 1; ++i)
    {
        int index = indexes.at(i);
        pyatnashki::position(current_row, current_col, index, count());

        int real_row = 0;
        int real_col = 0;
        pyatnashki::position(real_row, real_col, static_cast<int>(i + 1), count());

        Cell *dc = new Cell(valid_images ? images.at(i) : QImage(), real_row, real_col, current_row, current_col, this);

        QObject::connect(this, &Board::set_section, dc, &Cell::set_section);
        QObject::connect(dc, &Cell::cell_clicked, this, &Board::cell_clicked);
        m_cells.push_back(dc);
    }

    pyatnashki::position(current_row, current_col, indexes.back(), count());
    m_row_empty = current_row;
    m_column_empty = current_col;
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
    for (int i = 0; i < m_cells.size(); ++i)
    {
        Cell *dc = m_cells.at(i);
        if (dc->row() != dc->current_row() || dc->column() != dc->current_column())
            return;
    }

    game_over = true;

    if (movie)
    {
        movie->stop();
        delete movie;
        movie = nullptr;
    }

    QList<QGraphicsItem*> children = childItems();
    for (int i = 0; i < children.size(); ++i) children.at(i)->setVisible(false);

    movie = new QMovie(this);
    movie->setFileName(":/files/rick-roll.gif");
    movie->setScaledSize(boundingRect().size().toSize());
    QObject::connect(movie, &QMovie::frameChanged, [this](int frame) { current_frame = frame; update(); });
    movie->start();

    update();

    emit win();
}
