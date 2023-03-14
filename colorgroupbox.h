#ifndef COLORGROUPBOX_H
#define COLORGROUPBOX_H

#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include "ColorChangeListener.h"

class ColorGroupBox : public QGroupBox, public ColorChangeListener{
    Q_OBJECT
public:
    explicit ColorGroupBox(QWidget *parent = nullptr);
    QLineEdit * getLineEdit();
    QVBoxLayout * getLayout();
    virtual void colorChanged(QColor &) = 0;
private:
    QVBoxLayout * layout = new QVBoxLayout();
    QLineEdit * lineEdit = new QLineEdit();

};

#endif // COLORGROUPBOX_H
