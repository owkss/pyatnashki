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

    Cell(const QImage &img, const int r, const int c, int current_row, int current_col, Board *parent);
    ~Cell() override;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    int type() const override { return Type; }

    Board *board() const noexcept;

    int row() const noexcept;
    int column() const noexcept;
    int index() const noexcept;
    int section() const noexcept;

    int current_row() const noexcept;
    int current_column() const noexcept;
    int current_index() const noexcept;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant & value) override;

public slots:

private slots:
    void set_section(int s) noexcept;
    void set_new_position(int r, int c);

private:
    friend class Board;

    const int m_row;
    const int m_col;
    int m_section = 100;

    int m_current_row;
    int m_current_col;

    QImage m_image;

signals:
    void cell_clicked(Cell *dc);
};

#endif // CELL_H
