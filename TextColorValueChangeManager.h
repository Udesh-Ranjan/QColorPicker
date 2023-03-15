#ifndef TEXTCOLORVALUECHANGEMANAGER_H
#define TEXTCOLORVALUECHANGEMANAGER_H

#include <QColor>
#include "TextColorValueListener.h"

class TextColorValueChangeManager{
public:
    explicit TextColorValueChangeManager(){};
    virtual ~ TextColorValueChangeManager(){};
    virtual bool attachTextColorChangeListener(TextColorValueListener &) = 0;
    virtual bool detachTextColorChangeListener(TextColorValueListener &) = 0;
    virtual void notifyTextColorChangeListener(QColor &) = 0;
};

#endif // TEXTCOLORVALUECHANGEMANAGER_H
