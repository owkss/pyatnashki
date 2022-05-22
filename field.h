#ifndef FIELD_H
#define FIELD_H

#include <array>

#include <QGraphicsView>

class Board;
class Field : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Field(QWidget *parent = nullptr);
    ~Field() override;

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void resizeEvent(QResizeEvent * event) override;
    void contextMenuEvent(QContextMenuEvent * event) override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void dragEnterEvent(QDragEnterEvent *event)  override;
    void dragLeaveEvent(QDragLeaveEvent *event)  override;
    void dragMoveEvent(QDragMoveEvent *event)  override;
    void dropEvent(QDropEvent *event)  override;
    void wheelEvent(QWheelEvent *event) override;

    void drawBackground(QPainter *painter, const QRectF &rect) override;
    void drawForeground(QPainter *painter, const QRectF &rect) override;

    void scrollContentsBy(int dx, int dy) override;

private:
    QGraphicsScene *m_scene = nullptr;
    Board *m_board = nullptr;

signals:
    void side_changed(int s);
};

#endif // FIELD_H
