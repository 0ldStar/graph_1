#include <QApplication>
#include <QOpenGLWidget>
#include <QTranslator>
#include <iostream>
#include "Lines.h"
#include "SpinBox.h"

#define WIDTH 560
#define HEIGHT 540
#define COUNT 50

int main(int argc, char *argv[]) {

    /* MainWindow w;
     w.show();*//*
    int x1, x2, y1, y2;
    std::cin >> x1;
    std::cin >> x2;
    std::cin >> y1;
    std::cin >> y2;*/
    // if (abs(x1) <= WIDTH / 2 && abs(x2) <= WIDTH / 2 && abs(y1) <= HEIGHT / 2 && abs(y2) <= HEIGHT / 2) {
    QApplication a(argc, argv);
    Lines window(0, 100, 0, -200, WIDTH, HEIGHT, COUNT);
    //Lines window(x1, x2, y1, y2, COUNT);
    window.resize(WIDTH, HEIGHT);
    window.setWindowTitle("Lines");
    SpinBox box(&window);
    window.show();
    return a.exec();
    // }
    // return 0;
}
