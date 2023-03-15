#include "colorgroupbox.h"

ColorGroupBox::ColorGroupBox(QWidget *parent):QGroupBox{parent}{
    setTitle("HEX");
    setAlignment(Qt::AlignLeft);
    setFixedHeight(60);
    lineEdit->setFrame(false);
    //    QPalette * palette = new QPalette();
    //    palette->setColor(QPalette::Base, Qt::red);
    //    lineEdit->setPalette(*palette);
    lineEdit->setAlignment(Qt::AlignLeft);
    QFont * font = new QFont();
    font->setPixelSize(15);
    lineEdit->setFont(*font);
    layout->addWidget(lineEdit, Qt::AlignCenter, Qt::AlignCenter);
    setLayout(layout);
}

QLineEdit * ColorGroupBox::getLineEdit(){
    return lineEdit;
}

QHBoxLayout * ColorGroupBox::getLayout(){
    return layout;
}
