#ifndef SELECTEDCOLORPANEL_H
#define SELECTEDCOLORPANEL_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <Qt>
#include <QColor>
#include <QPen>
#include <QBrush>
#include <QRect>
#include <iostream>

#include "ColorChangeListener.h"

class SelectedColorPanel : public QWidget, public ColorChangeListener{
    Q_OBJECT
public:
    explicit SelectedColorPanel(QWidget *parent = nullptr);
    void colorChanged(QColor &);

protected:
    virtual void paintEvent(QPaintEvent * event);

private:
    QColor panelColor = Qt::red;

signals:

};

#endif // SELECTEDCOLORPANEL_H
