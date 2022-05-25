#ifndef BOARD_H
#define BOARD_H

#include <QGraphicsObject>

class Cell;
class QMovie;
class QImage;
class Board : public QGraphicsObject
{
    Q_OBJECT
public:
    enum { Type = UserType + 1 };

    Board(const QList<QImage> &images, int count, QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    int type() const override { return Type; }

    int side() const noexcept;
    int section() const noexcept;

    int count() const noexcept { return m_count; }

public slots:

private slots:
    void recalc_size(const QSize &sz) noexcept;
    void cell_clicked(Cell *dc);

private:
    friend class Field;

    void generate(const QList<QImage> &images);
    bool valid_move(int r, int c);
    void check_win();

    QVector<Cell*> m_cells;

    int m_count = 4;

    int m_row_empty = 0;
    int m_column_empty = 0;

    int m_section = 480;

    int current_frame = 0;
    QMovie *movie = nullptr;
    bool game_over = false;

signals:
    void set_section(int s);
    void step_has_been_taken();
    void win();
};

#endif // BOARD_H
