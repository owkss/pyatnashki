#ifndef BOARD_H
#define BOARD_H

#include <QGraphicsObject>

class Cell;
class QImage;
class DynamicCell;
class Board : public QGraphicsObject
{
    Q_OBJECT
public:
    enum { Type = UserType + 1 };

    Board(const QList<QImage> &images, int r = 4, int c = 4, QGraphicsItem *parent = nullptr);

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
    void cell_clicked(DynamicCell *dc);

private:
    friend class Field;

    void generate(const QList<QImage> &images);
    bool valid_move(int r, int c);
    void check_win();

    QVector<Cell*> m_static_cells;
    QVector<DynamicCell*> m_dynamic_cells;

    int m_rows = 4;
    int m_columns = 4;

    int m_row_empty = 0;
    int m_column_empty = 0;

    int m_section = 480;

signals:
    void set_section(int s);
    void win();
};

#endif // BOARD_H
