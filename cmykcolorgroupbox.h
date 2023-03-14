#ifndef CMYKCOLORGROUPBOX_H
#define CMYKCOLORGROUPBOX_H

#include "colorgroupbox.h"

class CmykColorGroupBox : public ColorGroupBox{
public:
    CmykColorGroupBox();
    void colorChanged(QColor &);
};

#endif // CMYKCOLORGROUPBOX_H
