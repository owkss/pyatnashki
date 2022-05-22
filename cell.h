#ifndef CELL_H
#define CELL_H

#include <QGraphicsObject>

class Board;
class Cell : public QGraphicsObject
{
    Q_OBJECT
public:
    enum { Type = UserType + 2 };

    Cell(int r, int c, Board *parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    int type() const override { return Type; }

    int row() const noexcept;
    int column() const noexcept;
    int index() const noexcept;
    int side() const noexcept;

    bool is_movable() const noexcept;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    Board *m_board = nullptr;

public slots:

private slots:
    void set_side(int s) noexcept;

private:
    friend class Board;

    const int m_row;
    const int m_col;

    int m_side = 100;

signals:

};

#endif // CELL_H
