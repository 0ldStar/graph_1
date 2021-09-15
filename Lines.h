//
// Created by 777 on 14.09.2021.
//

#ifndef UNTITLED14_LINES_H
#define UNTITLED14_LINES_H


#include <QWidget>

void drawCDA(int x1, int y1, int x2, int y2, int width, int height, QPainter &painter);

void drawBrezenham(int x1, int y1, int x2, int y2, int width, int height, QPainter &painter);

void decardToDigital(int x, int y, int &X, int &Y, int width, int height);

void digitalToDecard(int x, int y, int &X, int &Y, int width, int height);

class Lines : public QWidget {

public:
    Lines(int x1, int x2, int y1, int y2);

protected:
    void paintEvent(QPaintEvent *event);

    void drawLines(QPainter *qp);

private:
    int X1, X2, Y1, Y2;
};

#endif //UNTITLED14_LINES_H
