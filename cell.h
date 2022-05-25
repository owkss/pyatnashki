#ifndef CELL_H
#define CELL_H

#include <QImage>
#include <QGraphicsObject>

class Board;
class Cell : public QGraphicsObject
{
    Q_OBJECT
public:
    enum { Type = UserType + 2 };

    Cell(const int r, const int c, Board *parent);
    ~Cell() override;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    int type() const override { return Type; }

    Board *board() const noexcept;

    int row() const noexcept;
    int column() const noexcept;
    int index() const noexcept;
    int section() const noexcept;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

public slots:

private slots:
    void set_section(int s) noexcept;

private:
    friend class Board;

    const int m_row;
    const int m_col;

    int m_section = 100;

signals:

};

#endif // CELL_H
