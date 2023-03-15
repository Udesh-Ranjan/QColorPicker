#ifndef HEXCOLORGROUPBOX_H
#define HEXCOLORGROUPBOX_H

#include "colorgroupbox.h"
#include <QVBoxLayout>
#include <QWidget>
#include <QLineEdit>
#include <iostream>
#include <algorithm>
#include <QPushButton>
#include <QIcon>
#include <QGuiApplication>
#include <QApplication>

#include "TextColorValueChangeManager.h"

class HexColorGroupBox:public ColorGroupBox, public TextColorValueChangeManager, public TextColorValueListener{

public:
    explicit HexColorGroupBox(QWidget * parent = nullptr);
    virtual void colorChanged(QColor &);
    virtual void textColorValueChanged(QColor &);
    void resetCopyButton();

    class ColorChangeAction:public QObject{
    public:
        ColorChangeAction(HexColorGroupBox & hexColorGroupBox, QObject * parent=nullptr);

    public slots:
        void colorValueChanged(QString);
    private:
        HexColorGroupBox * hexColorGroupBox;
    };

    bool attachTextColorChangeListener(TextColorValueListener &);
    bool detachTextColorChangeListener(TextColorValueListener &);
    void notifyTextColorChangeListener(QColor &);

public slots:
    void copyButtonClicked();

private:
    std::vector<TextColorValueListener *> textColorValueListeners;
    QPushButton * copyButton = new QPushButton();
    bool copyFlag = true;
    QClipboard * clipboard = QApplication::clipboard();
};

#endif // HEXCOLORGROUPBOX_H
