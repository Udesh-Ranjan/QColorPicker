#ifndef CIRCULARBUTTON_H
#define CIRCULARBUTTON_H

#include <QColor>
#include <QPointF>
#include <QPainter>

class CircularButton{
public:
    CircularButton();
    void setRadius(float);
    void setCenter(float x, float y);
    void setCenter(QPointF center);
    void setColor(QColor color);

    float getRadius();
    QPointF getCenter();
    QColor getColor();

    void drawCircle(QPainter *);

private:
    float radius=12;
    QPointF center;

    QColor color;

};

#endif // CIRCULARBUTTON_H
