#ifndef DYNAMICCELL_H
#define DYNAMICCELL_H

#include "cell.h"

#include <QImage>

class Board;
class DynamicCell : public Cell
{
    Q_OBJECT
public:
    enum { Type = UserType + 3 };

    DynamicCell(const QImage &img, const int r, const int c, int current_row, int current_col, Board *parent);
    ~DynamicCell() override;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    int type() const override { return Type; }

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
    void set_new_position(int r, int c);

private:
    friend class Board;

    int m_current_row;
    int m_current_col;

    QImage m_image;

signals:
    void cell_clicked(DynamicCell *dc);
};

#endif // DYNAMICCELL_H
