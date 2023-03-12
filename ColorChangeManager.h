#ifndef COLORCHANGEMANAGER_H
#define COLORCHANGEMANAGER_H

#include "ColorChangeListener.h"

class ColorChangeManager{
public:
    ColorChangeManager(){};
    virtual ~ColorChangeManager(){};
    virtual bool attachColorChangeListener(ColorChangeListener &) = 0;
    virtual bool detachColorChangeListener(ColorChangeListener &) = 0;
    virtual void notifyColorChangeListener(QColor &) = 0;
};
#endif // COLORCHANGEMANAGER_H
