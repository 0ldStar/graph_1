//
// Created by 777 on 21.09.2021.
//

#include "SpinBox.h"
#include "Lines.h"
#include "sizes.h"
#include <QHBoxLayout>
#include <QLabel>
#include "spinbox.h"

SpinBox::SpinBox(QWidget *parent, int width, int height)
        : QWidget(parent) {

    QHBoxLayout *hbox = new QHBoxLayout(this);
    hbox->setSpacing(15);
    spinbox1 = new QSpinBox(this);
    spinbox1->setRange(-width / 2, width / 2);
    spinbox2 = new QSpinBox(this);
    spinbox2->setRange(-width / 2, width / 2);
    spinbox3 = new QSpinBox(this);
    spinbox3->setRange(-height / 2, height / 2);
    spinbox4 = new QSpinBox(this);
    spinbox4->setRange(-height / 2, height / 2);

    hbox->addWidget(spinbox1);
    hbox->addWidget(spinbox2);
    hbox->addWidget(spinbox3);
    hbox->addWidget(spinbox4);

/*
    connect(spinbox1, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            lbl, static_cast<void (QLabel::*)(int)>(&QLabel::setNum));
*/

}

int SpinBox::getX1() { return spinbox1->value(); }

int SpinBox::getX2() { return spinbox2->value(); }

int SpinBox::getY1() { return spinbox3->value(); }

int SpinBox::getY2() { return spinbox4->value(); }
