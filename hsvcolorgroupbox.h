#ifndef HSVCOLORGROUPBOX_H
#define HSVCOLORGROUPBOX_H

#include "colorgroupbox.h"

#include <algorithm>
#include <regex>
#include <string>
#include <iostream>

#include "TextColorValueChangeManager.h"

class HsvColorGroupBox : public ColorGroupBox,  public TextColorValueChangeManager, public TextColorValueListener{
public:
    HsvColorGroupBox();
    virtual void colorChanged(QColor &);
    virtual void textColorValueChanged(QColor &);

    class ColorChangeAction:public QObject{
    public:
        ColorChangeAction(HsvColorGroupBox & hsvColorGroupBox, QObject * parent=nullptr);

    public slots:
        void colorValueChanged(QString);
    private:
        HsvColorGroupBox * hsvColorGroupBox;
    };

    bool attachTextColorChangeListener(TextColorValueListener &);
    bool detachTextColorChangeListener(TextColorValueListener &);
    void notifyTextColorChangeListener(QColor &);
private:
    std::vector<TextColorValueListener *> textColorValueListeners;
};

#endif // HSVCOLORGROUPBOX_H
