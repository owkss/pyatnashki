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

    QPointF topleft(int r, int c, int side);
    void position(int &r, int &c, const int index, const int count);
    int gcd(int a, int b);
    QList<QImage> split(const QImage &img, const int count);
}

#endif // FUNCTIONS_H
