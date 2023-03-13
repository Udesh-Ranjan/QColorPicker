#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>

#include "slider.h"
#include "ColorChangeListener.h"
#include "selectedcolorpanel.h"
#include "rightpanelcircularbutton.h"
#include "ColorChangeManager.h"

class CentralWidget : public QWidget, public ColorChangeListener, ColorChangeManager{
    Q_OBJECT
public:
    explicit CentralWidget(QWidget *parent = nullptr);
    void updateRightPanel(QPainter * );
    virtual void colorChanged(QColor &);
    void moveCircularButton(QPointF point);

    bool attachColorChangeListener(ColorChangeListener &);
    bool detachColorChangeListener(ColorChangeListener &);
    void notifyColorChangeListener(QColor &);

protected:
    virtual void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

private:
    bool mouseClick = false;
    int rightPanelWidth = 385;
    int rightPanelHeight = 300;
    QRect rightSelectedArea;
    std::vector<std::vector<int> *>saturationValueVector;
    QColor * rightSelectedColor = new QColor(255, 0, 0);
    RightPanelCircularButton rightPanelCircularButton;
    SelectedColorPanel * selectedColorPanel = new SelectedColorPanel();
    Slider * slider = new Slider();
    std::vector<ColorChangeListener *>colorChangeListeners;
signals:

};

#endif // CENTRALWIDGET_H
