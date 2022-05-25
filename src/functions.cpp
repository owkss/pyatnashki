#include "functions.h"

#include <cmath>

#include <QDebug>
#include <QPointF>

QPointF pyatnashki::topleft(int r, int c, int side)
{
    return QPointF(side * c + MARGIN * c, side * r + MARGIN * r);
}

void pyatnashki::position(int &r, int &c, const int index, const int count)
{
    r = (index % count == 0) ? index / count - 1 : index / count;
    c = index - r * count - 1;
}

int pyatnashki::gcd(int a, int b)
{
    if (b == 0)
        return ::abs(a);
    return gcd(b, a % b);
}

QList<QImage> pyatnashki::split(const QImage &img, const int count)
{
    QList<QImage> list;
    if (img.isNull())
        return list;

    const int row_section = img.height() / count;
    const int col_section = img.width() / count;
    int x_offset = 0;
    int y_offset = 0;
    for (int i = 0; i < count; ++i)
    {
        x_offset = 0;
        for (int j = 0; j < count; ++j)
        {
            QRect rect(x_offset, y_offset, col_section, row_section);
            QImage copy = img.copy(rect);
            list.push_back(copy);

            x_offset += col_section;
        }

        y_offset += row_section;
    }

    return list;
}
