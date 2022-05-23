#ifndef BOARD_H
#define BOARD_H

#include <QGraphicsObject>

class Cell;
class DynamicCell;
class Board : public QGraphicsObject
{
    Q_OBJECT
public:
    enum { Type = UserType + 1 };

    Board(int r = 4, int c = 4, QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    int type() const override { return Type; }

    int width() const noexcept;
    int height() const noexcept;
    int section() const noexcept;

    int row_count() const noexcept    { return m_rows; }
    int column_count() const noexcept { return m_columns; }

public slots:

private slots:
    void recalc_size(const QSize &sz) noexcept;

private:
    friend class Field;

    void generate();

    QVector<QVector<Cell*>> m_static_cells;

    int m_rows = 4;
    int m_columns = 4;

    int m_section = 480;
};

#endif // BOARD_H
