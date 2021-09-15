#include <QPainter>
#include "lines.h"
#include <iostream>
#include <QWidget>

#define COUNT 20


Lines::Lines(int x1, int x2, int y1, int y2)
        : X1(x1), X2(x2), Y1(y1), Y2(y2) {}

void Lines::paintEvent(QPaintEvent *e) {

    Q_UNUSED(e);

    QPainter qp(this);
    drawLines(&qp);
}

void Lines::drawLines(QPainter *qp) {

    QPainter painter(this);
    int width = this->width();
    int height = this->height();
    int x1, x2, y1, y2;
    decardToDigital(X1, Y1, x1, y1, width, height);
    decardToDigital(X2, Y2, x2, y2, width, height);
    painter.setBrush(QBrush("#c50024"));
    drawBrezenham(X1, Y1, X2, Y2, width, height, painter);
    painter.setBrush(QBrush("#0000FF"));
    drawCDA(X1, Y1, X2, Y2, width, height, painter);
    painter.drawLine(x1, y1, x2, y2);
    painter.setPen(Qt::black);
    painter.setPen(Qt::DotLine);
    for (int i = 0; i < COUNT; ++i) {
        painter.drawLine(i / (float) COUNT * width, 0, i / (float) COUNT * width, height);
    }
    for (int i = 0; i < COUNT; ++i) {
        painter.drawLine(0, i / (float) COUNT * height, width, i / (float) COUNT * height);
    }
    painter.setPen(Qt::red);
    painter.drawLine(width / 2, 0, width / 2, height);
    painter.drawLine(0, height / 2, width, height / 2);


}


int sign(double x) {
    if (x > 0) return 1;
    else if (x == 0) return 0;
    else
        return -1;
}

void drawPixel(int x, int y, int width, int height, QPainter &painter) {
    double dx = width / (float) COUNT;
    double dy = height / (float) COUNT;
    painter.drawRect(x * dx, y * dy, dx, dy);
}

void drawCDA(int x1, int y1, int x2, int y2, int width, int height, QPainter &painter) {
    double dx, dy, l, x, y;
    int _x, _y;
    int i;
    double dX = width / (float) COUNT;
    double dY = height / (float) COUNT;
    if (abs(x2 - x1) >= abs(y2 - y1)) l = abs(x2 - x1);
    else {
        l = abs(y2 - y1);
    }
    dx = (x2 - x1) / l;
    dy = (y2 - y1) / l;

    x = x1 + 0.5 * sign(dx);
    y = y1 + 0.5 * sign(dy);

    i = 1;
    while (i <= l) {
        decardToDigital(floor(x), floor(y), _x, _y, width, height);
        drawPixel(_x / (int) dX, _y / (int) dY, width, height, painter);
        x = x + dx;
        y = y + dy;
        i = i + 1;
    }
}

void drawBrezenham(int x0, int y0, int x1, int y1, int width, int height, QPainter &painter) {

    int a = 0, b = 0, e = 0, dx, dy, sx, sy;

    int x = x0;
    int _x, _y;
    int y = y0;
    double dX = width / (float) COUNT;
    double dY = height / (float) COUNT;
    dx = abs(x1 - x0);

    dy = abs(y1 - y0);

    if ((x1 - x0) >= 0) sx = 1;
    else
        sx = -1;

    if ((y1 - y0) >= 0) sy = 1;

    else sy = -1;

    if (dy > dx) {

        a = dx;

        dx = dy;

        dy = a;

        b = 1;

    } else b = 0;

    e = 2 * dy - dx;

    for (int i = 0; i != dx; i++) {
        decardToDigital(x, y, _x, _y, width, height);
        drawPixel(_x / (int) dX, _y / (int) dY, width, height, painter);

        while (e >= 0) {

            if (b == 1)x = x + sx;

            else y = y + sy;

            e = e - 2 * dx;

        }

        if (b == 1) y = y + sy;

        else x = x + sx;

        e = e + 2 * dy;

    }


}

void decardToDigital(int x, int y, int &X, int &Y, int width, int height) {
    X = width / 2 + x;
    Y = height / 2 - y;
}

void digitalToDecard(int x, int y, int &X, int &Y, int width, int height) {
    if (x > width / 2) X = x - width / 2;
    else
        X = -(width / 2 - x);
    if (y > height / 2) Y = -(y - height / 2);
    else
        Y = height / 2 - y;
}
