#ifndef COLORGROUPBOX_H
#define COLORGROUPBOX_H

#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QIcon>
#include <iostream>

#include "ColorChangeListener.h"

class ColorGroupBox : public QGroupBox, public ColorChangeListener{
    Q_OBJECT
public:
    explicit ColorGroupBox(QWidget *parent = nullptr);
    QLineEdit * getLineEdit();
    QHBoxLayout * getLayout();
    virtual void colorChanged(QColor &) = 0;

private:
    QHBoxLayout * layout = new QHBoxLayout();
    QLineEdit * lineEdit = new QLineEdit();

};

#endif // COLORGROUPBOX_H
