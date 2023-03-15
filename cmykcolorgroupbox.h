#ifndef CMYKCOLORGROUPBOX_H
#define CMYKCOLORGROUPBOX_H

#include "colorgroupbox.h"


#include <QLineEdit>
#include <iostream>
#include <algorithm>
#include "TextColorValueChangeManager.h"
#include <string>
#include <regex>

class CmykColorGroupBox : public ColorGroupBox, public TextColorValueChangeManager, public TextColorValueListener{
public:
    explicit CmykColorGroupBox();
    virtual void colorChanged(QColor &);
    virtual void textColorValueChanged(QColor &);

    class ColorChangeAction:public QObject{
    public:
        ColorChangeAction(CmykColorGroupBox & cmykColorGroupBox, QObject * parent=nullptr);
    public slots:
        void colorValueChanged(QString);
    private:
        CmykColorGroupBox * cmykColorGroupBox;
    };

    bool attachTextColorChangeListener(TextColorValueListener &);
    bool detachTextColorChangeListener(TextColorValueListener &);
    void notifyTextColorChangeListener(QColor &);
private:
    std::vector<TextColorValueListener *> textColorValueListeners;
};

#endif // CMYKCOLORGROUPBOX_H
