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

    Board(QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    int type() const override { return Type; }

    int side() const noexcept;
    int section() const noexcept;

    int row_empty() const noexcept { return m_row_empty; }
    int col_empty() const noexcept { return m_col_empty; }

public slots:

private slots:
    void selection_changed(int r, int c);
    void cell_clicked(int r, int c);
    void set_side(int s) noexcept;

private:
    friend class Field;

    Cell* m_static_cells[4][4];
    QVector<DynamicCell*> m_cells;

    int m_row_empty = 3; // Строка пустой ячейки
    int m_col_empty = 3; // Столбец пустой ячейки

    int m_row_select = -1; // Строка выделенной ячейки
    int m_col_select = -1; // Столбец выделенной ячейки

    int m_side = 480;
};

#endif // BOARD_H
