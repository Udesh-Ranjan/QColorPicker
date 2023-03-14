#include "hexcolorgroupbox.h"

HexColorGroupBox::HexColorGroupBox(QWidget * parent):ColorGroupBox{parent}{
    setTitle("HEX");
    setAlignment(Qt::AlignCenter);
    getLineEdit()->setAlignment(Qt::AlignCenter);
//    QVBoxLayout * layout = new QVBoxLayout();
//    QLineEdit * lineEdit = new QLineEdit("#ddj");
//    lineEdit->setFrame(false);

//    QPalette * palette = new QPalette();
////    palette->setColor(QPalette::Base, Qt::red);
//    lineEdit->setPalette(*palette);
//    lineEdit->setAlignment(Qt::AlignCenter);
//    QFont * font = new QFont();
//    font->setPixelSize(20);
//    lineEdit->setFont(*font);

//    layout->addWidget(lineEdit);
//    setLayout(layout);
}

void HexColorGroupBox::colorChanged(QColor & color){
    std::cout<<"Hex Color Changed : "<<color.name().toStdString()<<std::endl;
    getLineEdit()->setText(color.name());
}
