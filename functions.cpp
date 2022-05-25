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

QPointF pyatnashki::topleft(int r, int c, int side)
{
    return QPointF(side * c + MARGIN * c, side * r + MARGIN * r);
}

void pyatnashki::position(int &c, int &r, const int index, const int columns)
{
    r = (index % columns == 0) ? index / columns - 1 : index / columns;
    c = index - r * columns - 1;
}

QList<QImage> pyatnashki::split(const QImage &img, const int rows, const int columns)
{
    QList<QImage> list;

    const int row_section = img.height() / rows;
    const int col_section = img.width() / columns;
    int x_offset = 0;
    int y_offset = 0;
    for (int i = 0; i < rows; ++i)
    {
        x_offset = 0;
        for (int j = 0; j < columns; ++j)
        {
            QImage copy = img.copy(x_offset, y_offset, col_section, row_section);
            list.push_back(copy);

            x_offset += col_section;
        }

        y_offset += row_section;
    }

    return list;
}
