#ifndef FUNCTIONS_H
#define FUNCTIONS_H

class QPointF;

namespace pyatnashki
{
    enum Attributes
    {
        MARGIN = 5
    };

    QPointF topleft(int index, int side, const int rows, const int columns);
    int gcd(int a, int b);
}

#endif // FUNCTIONS_H
