#ifndef HEXCOLORGROUPBOX_H
#define HEXCOLORGROUPBOX_H

#include "colorgroupbox.h"
#include <QVBoxLayout>
#include <QWidget>
#include <QLineEdit>
#include <iostream>

class HexColorGroupBox:public ColorGroupBox{
public:
    HexColorGroupBox(QWidget * parent = nullptr);
    virtual void colorChanged(QColor &);
};

#endif // HEXCOLORGROUPBOX_H
