#ifndef RIGHTPANELCIRCULARBUTTON_H
#define RIGHTPANELCIRCULARBUTTON_H

#include <QPointF>
#include <QColor>
#include <QPainter>
#include <QPaintEvent>

class RightPanelCircularButton{

public:
    RightPanelCircularButton();
    void setRadius(float);
    void setCenter(float x, float y);
    void setCenter(QPointF center);
    void setColor(QColor color);

    float getRadius();
    QPointF getCenter();
    QColor getColor();

    void drawCircle(QPainter *);

private:
    float radius=15;
    QPointF center;

    QColor color;
};

#endif // RIGHTPANELCIRCULARBUTTON_H
