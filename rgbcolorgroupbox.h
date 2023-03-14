#ifndef RGBCOLORGROUPBOX_H
#define RGBCOLORGROUPBOX_H

#include "colorgroupbox.h"

class RgbColorGroupBox : public ColorGroupBox{
public:
    RgbColorGroupBox();
    virtual void colorChanged(QColor &);
};

#endif // RGBCOLORGROUPBOX_H
