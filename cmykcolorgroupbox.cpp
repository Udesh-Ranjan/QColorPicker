#include "cmykcolorgroupbox.h"

CmykColorGroupBox::CmykColorGroupBox(){
    setTitle("CMYK");
}

void CmykColorGroupBox::colorChanged(QColor & color){
    int c = int(color.cyan() * 100.0 / 255.0);
    int m = int(color.magenta() * 100.0 / 255.0);
    int y = int(color.yellow() * 100.0 / 255.0);
    int k = int(color.black() * 100.0 / 255.0);

    getLineEdit()->setText(QString::fromStdString(
                               std::to_string(c) + "%, " +
                               std::to_string(m) + "%, " +
                               std::to_string(y) + "%, " +
                               std::to_string(k)));
}
