#ifndef HSVCOLORGROUPBOX_H
#define HSVCOLORGROUPBOX_H

#include "colorgroupbox.h"

class HsvColorGroupBox : public ColorGroupBox{
public:
    HsvColorGroupBox();
    void colorChanged(QColor &);
};

#endif // HSVCOLORGROUPBOX_H
