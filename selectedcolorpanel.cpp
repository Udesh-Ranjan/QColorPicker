#include "selectedcolorpanel.h"

SelectedColorPanel::SelectedColorPanel(QWidget *parent)
    : QWidget{parent}{
    setFixedSize(300, 300);
}

void SelectedColorPanel::colorChanged(QColor & color){
    std::cout<<"Color Changed Called"<<std::endl;
    panelColor.setRgb(color.rgb());
    repaint();
}
//void SelectedColorPanel::paintEvent(QPaintEvent * event){
//    QPainter painter(this);
//}

void SelectedColorPanel::paintEvent(QPaintEvent * event){
    QPainter painter(this);
    QPen pen;
    pen.setColor(panelColor);
    QBrush brush;
    brush.setColor(panelColor);
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    painter.setPen(pen);
    QRect rect(0, 0, width(), height());
    painter.fillRect(rect, brush);
}
