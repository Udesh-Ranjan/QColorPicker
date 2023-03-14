#include "rgbcolorgroupbox.h"

RgbColorGroupBox::RgbColorGroupBox(){
    setTitle("RGB");
}

void RgbColorGroupBox::colorChanged(QColor & color){
    getLineEdit()->setText(QString::fromStdString(std::to_string(color.red()) + ", " + std::to_string(color.green()) + ", " + std::to_string(color.blue())));
}
