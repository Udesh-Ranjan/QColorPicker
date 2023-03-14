#include "hslcolorgroupbox.h"

HslColorGroupBox::HslColorGroupBox(){
    setTitle("HSL");
}

void HslColorGroupBox::colorChanged(QColor & color){
    int hue = color.hue();
    int saturation = std::max(std::min(int(color.saturation() * 100.0 / 255.0 + .5), 100), 0);
    int lightness = std::max(std::min(int(color.lightness() * 100.0 / 255.0 + .5), 100), 0);

    getLineEdit()->setText(
                QString::fromStdString(
                    std::to_string(hue) + "°, " +
                    std::to_string(saturation) + "%, " +
                    std::to_string(lightness) + "%"));
}
