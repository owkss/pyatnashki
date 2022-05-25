#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QList>
#include <QImage>
#include <QPointF>

namespace pyatnashki
{
    enum Attributes
    {
        MARGIN = 5
    };

    QPointF topleft(int index, int side, const int rows, const int columns);
    QPointF topleft(int r, int c, int side);
    void position(int &r, int &c, const int index, const int columns);
    int gcd(int a, int b);
    QList<QImage> split(const QImage &img, const int rows, const int columns);
}

#endif // FUNCTIONS_H
