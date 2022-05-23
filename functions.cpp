#include "functions.h"

#include <cmath>

#include <QDebug>
#include <QPointF>

QPointF pyatnashki::topleft(int index, int side, const int rows, const int columns)
{
    if (index <= 0 || index > rows * columns)
        return QPointF(0, 0);

    int r = index / columns;
    if (index % columns == 0)
        r -= 1;
    int c = index - r * columns - 1;

    return QPointF(side * c + MARGIN * c, side * r + MARGIN * r);
}

int pyatnashki::gcd(int a, int b)
{
    if (b == 0)
        return ::abs(a);
    return gcd(b, a % b);
}
