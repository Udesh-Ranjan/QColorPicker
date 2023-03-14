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
#include "hexcolorgroupbox.h"
#include "rgbcolorgroupbox.h"
#include "cmykcolorgroupbox.h"
#include "hsvcolorgroupbox.h"
#include "hslcolorgroupbox.h"

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

    void updateLeftPanel(QPainter *);

protected:
    virtual void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

private:
    bool mouseClick = false;
    int rightPanelWidth = 485;
    int rightPanelHeight = 300;
    QRect rightSelectedArea;
    std::vector<std::vector<int> *>saturationValueVector;
    QColor * rightSelectedColor = new QColor(255, 0, 0);
    RightPanelCircularButton rightPanelCircularButton;
    SelectedColorPanel * selectedColorPanel = new SelectedColorPanel();
    Slider * slider = new Slider();
    std::vector<ColorChangeListener *>colorChangeListeners;

    HexColorGroupBox * hexColorGroupBox = new HexColorGroupBox();
    RgbColorGroupBox * rgbColorGroupBox = new RgbColorGroupBox();
    CmykColorGroupBox * cmykColorGroupBox = new CmykColorGroupBox();
    HsvColorGroupBox * hsvColorGroupBox = new HsvColorGroupBox();
    HslColorGroupBox * hslColorGroupBox = new HslColorGroupBox();

};

#endif // CENTRALWIDGET_H
