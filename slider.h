#ifndef SLIDER_H
#define SLIDER_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <iostream>
#include <vector>
#include <QColor>
#include <QPen>

#include "circularbutton.h"
#include "ColorChangeManager.h"
#include "ColorChangeListener.h"

class Slider : public QWidget, public ColorChangeManager{
    Q_OBJECT
public:
    explicit Slider(QWidget *parent = nullptr);
    void initializeSlider();
    void drawSlider(QPaintEvent * event, QPainter * painter);
    void moveCircularButton(QPointF);
    virtual bool attachColorChangeListener(ColorChangeListener &);
    virtual bool detachColorChangeListener(ColorChangeListener &);
    virtual void notifyColorChangeListener(QColor &);

protected:

    virtual void paintEvent(QPaintEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);

private:
    int sliderWidth = 600;
    int sliderHeight = 20;
    int windowWidth = 700;
    int windowHeight = 300;
    std::vector<std::vector<int>>colors;
    CircularButton circularButton;
    bool mouseClick;
    std::vector<ColorChangeListener *>colorChangeListeners;

};
#endif // SLIDER_H
