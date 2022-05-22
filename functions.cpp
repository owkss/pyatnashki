#include "functions.h"

#include <QPointF>

QPointF tag::topleft(int index, int side)
{
    switch (index)
    {
    case 0: case 1: case 2: case 3:
        return QPointF(side * index + MARGIN * index, 0);
    case 4: case 5: case 6: case 7:
        return QPointF(side * (index - 4) + MARGIN * (index - 4), side + MARGIN);
    case 8: case 9: case 10: case 11:
        return QPointF(side * (index - 8) + MARGIN * (index - 8), side * 2 + MARGIN * 2);
    case 12: case 13: case 14: case 15:
        return QPointF(side * (index - 12) + MARGIN * (index - 12), side * 3 + MARGIN * 3);
    default:
        break;
    }

    return QPointF(0, 0);
}
