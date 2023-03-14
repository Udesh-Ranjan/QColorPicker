#include "selectedcolorpanel.h"

SelectedColorPanel::SelectedColorPanel(){
}

//void SelectedColorPanel::colorChanged(QColor & color){
//    std::cout<<"Color Changed Called"<<std::endl;
//    panelColor.setRgb(color.rgb());
//}
//void SelectedColorPanel::paintEvent(QPaintEvent * event){
//    QPainter painter(this);
//}

void SelectedColorPanel::paintPanel(QPainter * painter){
//    QPainter painter(this);
    QPen pen;
    pen.setColor(panelColor);
    QBrush brush;
    brush.setColor(panelColor);
    brush.setStyle(Qt::SolidPattern);
    painter->setBrush(brush);
    painter->setPen(pen);
    QRect rect(startX, startY, screenWidth + startX, screenHeight + startY);
    painter->fillRect(rect, brush);
}

int SelectedColorPanel::getScreenWidth(){
    return screenWidth;
}

int SelectedColorPanel::getScreenHeight(){
    return screenHeight;
}

int SelectedColorPanel::getStartX(){
    return startX;
}

int SelectedColorPanel::getStartY(){
    return startY;
}

void SelectedColorPanel::setStartX(int x){
    startX = x;
}

void SelectedColorPanel::setStartY(int y){
    startY = y;
}

void SelectedColorPanel::setPanelColor(QColor color){
    panelColor.setRgb(color.rgb());
}
