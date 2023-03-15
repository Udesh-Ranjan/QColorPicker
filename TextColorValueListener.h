#ifndef TEXTCOLORVALUELISTENER_H
#define TEXTCOLORVALUELISTENER_H

#include <QColor>

class TextColorValueListener{
public:
    TextColorValueListener(){};
    virtual ~TextColorValueListener(){};
    virtual void textColorValueChanged(QColor &) = 0;
};
#endif // TEXTCOLORVALUELISTENER_H
