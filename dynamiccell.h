#ifndef DYNAMICCELL_H
#define DYNAMICCELL_H

#include "cell.h"

class Board;
class DynamicCell : public Cell
{
    Q_OBJECT
public:
    enum { Type = UserType + 2 };

    DynamicCell(int r, int c, Board *parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    int type() const override { return Type; }

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant & value) override;

public slots:

private slots:

private:

signals:
    void selection_changed(int r, int c);
};

#endif // DYNAMICCELL_H
