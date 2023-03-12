#include "circularbutton.h"

CircularButton::CircularButton(){

}
void CircularButton::setRadius(float radius){
    this->radius = radius;
}

float CircularButton::getRadius(){
    return radius;
}

QPointF CircularButton::getCenter(){
    return center;
}

void CircularButton::setCenter(float x, float y){
    center.setX(x);
    center.setY(y);
}
void CircularButton::setCenter(QPointF center){
    this->center.setX(center.x());
    this->center.setY(center.y());
}

void CircularButton::setColor(QColor color){
    this->color.setRgba(color.rgba());
}

QColor CircularButton::getColor(){
    return color;
}

void CircularButton::drawCircle(QPainter * painter){
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
