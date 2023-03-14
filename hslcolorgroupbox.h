#ifndef HSLCOLORGROUPBOX_H
#define HSLCOLORGROUPBOX_H

#include "colorgroupbox.h"

class HslColorGroupBox : public ColorGroupBox{
public:
    HslColorGroupBox();
    void colorChanged(QColor &);
};

#endif // HSLCOLORGROUPBOX_H
