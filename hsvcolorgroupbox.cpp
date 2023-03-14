#include "hsvcolorgroupbox.h"

HsvColorGroupBox::HsvColorGroupBox(){
    setTitle("HSV");
}

void HsvColorGroupBox::colorChanged(QColor & color){
    int hue = color.hue();
    int saturation = std::max(
                std::min(int(color.saturation() * 100.0 / 255.0 + .5), 100), 0);
    int value = std::max(
                std::min(int(color.value() * 100.0 / 255.0 + .5), 100), 0);

    getLineEdit()->setText(
                QString::fromStdString(
                    std::to_string(hue) + "°, " +
                    std::to_string(saturation) + "%, " +
                    std::to_string(value) + "%"));
}
