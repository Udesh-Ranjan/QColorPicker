#ifndef COLORCHANGELISTENER_H
#define COLORCHANGELISTENER_H

#include <QColor>

class ColorChangeListener{
public:
    ColorChangeListener(){};
    virtual ~ColorChangeListener(){};

    virtual void colorChanged(QColor &) = 0;

};
#endif // COLORCHANGELISTENER_H
