//
// Created by 777 on 21.09.2021.
//

#include "SpinBox.h"
#include "Lines.h"
#include "sizes.h"
#include <QHBoxLayout>
#include <QLabel>
#include "spinbox.h"

SpinBox::SpinBox(QWidget *parent)
        : QWidget(parent) {

    QHBoxLayout *hbox = new QHBoxLayout(this);
    hbox->setSpacing(15);

    spinbox1 = new QSpinBox(this);
    spinbox2 = new QSpinBox(this);
    spinbox3 = new QSpinBox(this);
    spinbox4 = new QSpinBox(this);

    hbox->addWidget(spinbox1);
    hbox->addWidget(spinbox2);
    hbox->addWidget(spinbox3);
    hbox->addWidget(spinbox4);

    connect(spinbox1, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            lbl, static_cast<void (QLabel::*)(int)>(&QLabel::setNum));

}

SpinBox::dataReciew() {

}