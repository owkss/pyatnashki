#include "field.h"
#include "board.h"
#include "functions.h"

#include <iostream>

#include <QDebug>
#include <QResizeEvent>

Field::Field(QWidget *parent)
    : QGraphicsView(parent)
{
    setObjectName("field");

    m_scene = new QGraphicsScene(this);
    m_scene->setObjectName("field_scene");
    setScene(m_scene);

    setCacheMode(QGraphicsView::CacheBackground);
    setOptimizationFlags(QGraphicsView::DontSavePainterState);

    m_board = new Board;
    m_scene->addItem(m_board);
}

Field::~Field()
{

}

void Field::generate_board(int r, int c)
{
    m_scene->removeItem(m_board);
    delete m_board;

    m_board = new Board(r, c);
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
    painter->fillRect(rect, Qt::white);
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
    m_board->recalc_size(viewport()->size());
    double x = (viewport()->width() + pyatnashki::MARGIN - m_board->boundingRect().width()) / 2;
    double y = (viewport()->height() + pyatnashki::MARGIN - m_board->boundingRect().height()) / 2;
    m_board->setPos(x, y);
}
