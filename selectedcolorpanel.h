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

class SelectedColorPanel {
public:
    SelectedColorPanel();
    int getScreenWidth();
    int getScreenHeight();
    int getStartX();
    int getStartY();
    void setStartX(int);
    void setStartY(int);
    void paintPanel(QPainter * painter);
    QColor getPanelColor();
    void setPanelColor(QColor color);

private:
    QColor panelColor = Qt::red;
    int screenWidth = 300;
    int screenHeight = 289;
    int startX=10, startY=10;
};

#endif // SELECTEDCOLORPANEL_H
