#ifndef HSLCOLORGROUPBOX_H
#define HSLCOLORGROUPBOX_H

#include "colorgroupbox.h"


#include <algorithm>
#include <regex>
#include <string>
#include <iostream>

#include "TextColorValueChangeManager.h"

class HslColorGroupBox : public ColorGroupBox ,  public TextColorValueChangeManager, public TextColorValueListener{
public:
    HslColorGroupBox();
    void colorChanged(QColor &);
    virtual void textColorValueChanged(QColor &);

    class ColorChangeAction:public QObject{
    public:
        ColorChangeAction(HslColorGroupBox & hslColorGroupBox, QObject * parent=nullptr);

    public slots:
        void colorValueChanged(QString);
    private:
        HslColorGroupBox * hslColorGroupBox;
    };

    bool attachTextColorChangeListener(TextColorValueListener &);
    bool detachTextColorChangeListener(TextColorValueListener &);
    void notifyTextColorChangeListener(QColor &);
private:
    std::vector<TextColorValueListener *> textColorValueListeners;
};

#endif // HSLCOLORGROUPBOX_H
