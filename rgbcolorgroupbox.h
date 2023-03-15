#ifndef RGBCOLORGROUPBOX_H
#define RGBCOLORGROUPBOX_H

#include "colorgroupbox.h"

#include <QLineEdit>
#include <iostream>
#include <algorithm>
#include <regex>
#include<string>

#include "TextColorValueChangeManager.h"

class RgbColorGroupBox : public ColorGroupBox, public TextColorValueChangeManager, public TextColorValueListener{
public:
    RgbColorGroupBox();
    virtual void colorChanged(QColor &);
    virtual void textColorValueChanged(QColor &);

    class ColorChangeAction:public QObject{
    public:
        ColorChangeAction(RgbColorGroupBox & rgbColorGroupBox, QObject * parent=nullptr);

    public slots:
        void colorValueChanged(QString);
    private:
        RgbColorGroupBox * rgbColorGroupBox;
    };

    bool attachTextColorChangeListener(TextColorValueListener &);
    bool detachTextColorChangeListener(TextColorValueListener &);
    void notifyTextColorChangeListener(QColor &);
private:
    std::vector<TextColorValueListener *> textColorValueListeners;
};

#endif // RGBCOLORGROUPBOX_H
