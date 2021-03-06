#include "field.h"
#include "board.h"
#include "functions.h"

#include <iostream>

#include <QDebug>
#include <QImage>
#include <QResizeEvent>

Field::Field(QWidget *parent)
    : QGraphicsView(parent)
    , m_background_color(Qt::white)
{
    setObjectName("field");

    m_scene = new QGraphicsScene(this);
    m_scene->setObjectName("field_scene");
    setScene(m_scene);

    setCacheMode(QGraphicsView::CacheBackground);
    setOptimizationFlags(QGraphicsView::DontSavePainterState);
}

Field::~Field()
{

}

void Field::set_background_color(const QColor &color)
{
    m_background_color = color;
    resetCachedContent();
}

void Field::generate_board(int count, const QImage &img)
{
    if (m_board)
    {
        m_scene->removeItem(m_board);
        delete m_board;
        m_board = nullptr;
    }

    QList<QImage> images = pyatnashki::split(img, count);

    m_board = new Board(images, count);
    QObject::connect(m_board, &Board::win, this, &Field::win);
    QObject::connect(m_board, &Board::step_has_been_taken, this, &Field::step_has_been_taken);
    m_scene->addItem(m_board);

    configure_board_size();
}

void Field::keyPressEvent(QKeyEvent *event)
{
    QGraphicsView::keyPressEvent(event);
}

void Field::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    m_scene->setSceneRect(QRectF(QPointF(0, 0), viewport()->size()));

    configure_board_size();
}

void Field::contextMenuEvent(QContextMenuEvent *event)
{
    QGraphicsView::contextMenuEvent(event);
}

void Field::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
}

void Field::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);
}

void Field::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);
}

void Field::dragEnterEvent(QDragEnterEvent *event)
{
    QGraphicsView::dragEnterEvent(event);
}

void Field::dragLeaveEvent(QDragLeaveEvent *event)
{
    QGraphicsView::dragLeaveEvent(event);
}

void Field::dragMoveEvent(QDragMoveEvent *event)
{
    QGraphicsView::dragMoveEvent(event);
}

void Field::dropEvent(QDropEvent *event)
{
    QGraphicsView::dropEvent(event);
}

void Field::wheelEvent(QWheelEvent *event)
{
    QGraphicsView::wheelEvent(event);
}

void Field::drawBackground(QPainter *painter, const QRectF &rect)
{
    painter->save();
    painter->fillRect(rect, m_background_color);
    painter->restore();
}

void Field::drawForeground(QPainter *painter, const QRectF &rect)
{
    QGraphicsView::drawForeground(painter, rect);
}

void Field::scrollContentsBy(int dx, int dy)
{
    QGraphicsView::scrollContentsBy(dx, dy);
}

void Field::configure_board_size()
{
    if (!m_board)
        return;

    m_board->recalc_size(viewport()->size());
    double x = (viewport()->width() + pyatnashki::MARGIN - m_board->boundingRect().width()) / 2;
    double y = (viewport()->height() + pyatnashki::MARGIN - m_board->boundingRect().height()) / 2;
    m_board->setPos(x, y);
}
