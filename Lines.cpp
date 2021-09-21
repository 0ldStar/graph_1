#include <QPainter>
#include <iostream>
#include <QWidget>
#include <QTimer>
#include <QKeyEvent>
#include <windows.h>
#include "Lines.h"


Lines::Lines(int x1, int x2, int y1, int y2, int width, int height, int count)
        : size{x1, x2, y1, y2, width, height, count} { flag = false; }

void Lines::keyPressEvent(QKeyEvent *event) {

    if (event->key() == Qt::Key_Escape) {
        flag = !flag;
        update();
    }
}

void Lines::paintEvent(QPaintEvent *e) {

    Q_UNUSED(e);
    QPainter qp(this);
    drawLines(qp);
    std::cout << "-" << flag << std::endl;
    if (flag) drawLines2(qp);
    drawRealLine(size, qp);
    drawGrid(size, qp);
    drawAxes(size, qp);
}

void Lines::drawLines2(QPainter &painter) {
    painter.setBrush(QBrush(Qt::red));
    painter.setPen(Qt::red);
    drawCDA(size, painter);
}

void Lines::drawLines(QPainter &painter) {
    painter.setBrush(QBrush(Qt::darkBlue));
    painter.setPen(Qt::darkBlue);
    drawBrezenham(size, painter);
}

void drawRealLine(sizes &size, QPainter &painter) {
    int x1, x2, y1, y2;
    painter.setBrush(QBrush(Qt::green));
    painter.setPen(Qt::green);
    decardToDigital(size.x1, size.y1, x1, y1, size.width, size.height);
    decardToDigital(size.x2, size.y2, x2, y2, size.width, size.height);
    painter.drawLine(x1, y1, x2, y2);
}

void drawGrid(sizes &size, QPainter &painter) {
    painter.setPen(Qt::black);
    painter.setPen(Qt::DotLine);
    for (int i = 0; i < size.count; ++i) {
        painter.drawLine((int) ((float) i / (float) size.count * (float) size.width), 0,
                         (int) ((float) i / (float) size.count * (float) size.width),
                         size.height);
    }
    for (int i = 0; i < size.count; ++i) {
        painter.drawLine(0, (int) ((float) i / (float) size.count * (float) size.height), size.width,
                         (int) ((float) i / (float) size.count * (float) size.height));
    }
}

void drawAxes(sizes &size, QPainter &painter) {
    painter.setPen(Qt::red);
    int dx = (int) ((float) size.width / 2);
    int dy = (int) ((float) size.height / 2);

    painter.drawLine(dx, 0, dx, size.height);
    painter.drawLine(0, dy, size.width, dy);
}

int sign(double x) {
    if (x > 0) return 1;
    else if (x == 0) return 0;
    else
        return -1;
}

void drawPixel(int x, int y, const sizes &size, QPainter &painter) {
    double dx = (float) size.width / (float) size.count;
    double dy = (float) size.height / (float) size.count;
    painter.drawRect((int) ((int) (x / dx) * dx), (int) (((int) (y / dy) * dy)), (int) dx, (int) dy);
}

void drawCDA(const sizes &size, QPainter &painter) {
    double dx, dy, l, x, y;
    int _x, _y;
    if (abs(size.x2 - size.x1) >= abs(size.y2 - size.y1)) l = abs(size.x2 - size.x1);
    else {
        l = abs(size.y2 - size.y1);
    }
    dx = (size.x2 - size.x1) / l;
    dy = (size.y2 - size.y1) / l;

    x = size.x1 + 0.5 * sign(dx);
    y = size.y1 + 0.5 * sign(dy);
    for (int i = 0; i < l; ++i) {
        decardToDigital(floor(x), floor(y), _x, _y, size.width, size.height);
        //drawPixel(_x / (int) dX, _y / (int) dY, size, painter);
        drawPixel(_x, _y, size, painter);
        x = x + dx;
        y = y + dy;
    }
}

void drawBrezenham(const sizes &size, QPainter &painter) {
    int a, b, e, dx, dy, sx, sy;

    int x = size.x1;
    int _x, _y;
    int y = size.y1;
    dx = abs(size.x2 - size.x1);
    dy = abs(size.y2 - size.y1);
    if ((size.x2 - size.x1) >= 0) sx = 1;
    else
        sx = -1;
    if ((size.y2 - size.y1) >= 0) sy = 1;
    else sy = -1;
    if (dy > dx) {
        a = dx;
        dx = dy;
        dy = a;
        b = 1;
    } else b = 0;
    e = 2 * dy - dx;
    for (int i = 0; i != dx; i++) {
        decardToDigital(x, y, _x, _y, size.width, size.height);
        drawPixel(_x, _y, size, painter);
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
