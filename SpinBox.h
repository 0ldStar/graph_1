//
// Created by 777 on 21.09.2021.
//

#ifndef UNTITLED14_SPINBOX_H
#define UNTITLED14_SPINBOX_H


#include <QWidget>
#include <QSpinBox>

class SpinBox : public QWidget {

Q_OBJECT

public:
    SpinBox(QWidget *parent = 0);

private:
    void dataReciewe();
    QSpinBox *spinbox1;
    QSpinBox *spinbox2;
    QSpinBox *spinbox3;
    QSpinBox *spinbox4;
};

#endif //UNTITLED14_SPINBOX_H
