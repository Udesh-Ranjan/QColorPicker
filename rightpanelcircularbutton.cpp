#include "rightpanelcircularbutton.h"

RightPanelCircularButton::RightPanelCircularButton(){

}

void RightPanelCircularButton::setRadius(float radius){
    this->radius = radius;
}

float RightPanelCircularButton::getRadius(){
    return radius;
}

QPointF RightPanelCircularButton::getCenter(){
    return center;
}

void RightPanelCircularButton::setCenter(float x, float y){
    center.setX(x);
    center.setY(y);
}
void RightPanelCircularButton::setCenter(QPointF center){
    this->center.setX(center.x());
    this->center.setY(center.y());
}

void RightPanelCircularButton::setColor(QColor color){
    this->color.setRgba(color.rgba());
}

QColor RightPanelCircularButton::getColor(){
    return color;
}

void RightPanelCircularButton::drawCircle(QPainter * painter){
    painter->setRenderHint(QPainter::Antialiasing);
    QPen pen;
    pen.setWidth(2);
    pen.setColor(Qt::white);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color.rgb());

    painter->setPen(pen);
    painter->setBrush(brush);

    painter->drawEllipse(center, radius, radius);
}
