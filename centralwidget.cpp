#include "centralwidget.h"
#include "hexcolorgroupbox.h"

#include <QVBoxLayout>
#include <Qt>
#include <QLabel>
#include "TextColorValueListener.h"

CentralWidget::CentralWidget(QWidget *parent): QWidget{parent}{
    setFixedSize(800, 600);
    QVBoxLayout * vLayout = new QVBoxLayout();
    vLayout->setContentsMargins(5, 300, 5, 0);

    vLayout->setAlignment(Qt::AlignHCenter);
    QWidget * widget = new QWidget();
    widget->setFixedHeight(80);
    QHBoxLayout * layout = new QHBoxLayout();
    layout->addWidget(slider);
    widget->setLayout(layout);
    vLayout->addWidget(widget);
    vLayout->addWidget(hexColorGroupBox);
    QWidget * colorWidgets = new QWidget();
    colorWidgets->setFixedHeight(70);
    QHBoxLayout * colorWidgetLayout = new QHBoxLayout();
    colorWidgetLayout->setSpacing(10);
    colorWidgetLayout->addWidget(rgbColorGroupBox);
    colorWidgetLayout->addWidget(cmykColorGroupBox);
    colorWidgetLayout->addWidget(hsvColorGroupBox);
    colorWidgetLayout->addWidget(hslColorGroupBox);

    QColor col(255, 0 ,0);
    rgbColorGroupBox->colorChanged(col);
    cmykColorGroupBox->colorChanged(col);
    hsvColorGroupBox->colorChanged(col);
    hslColorGroupBox->colorChanged(col);
    hexColorGroupBox->colorChanged(col);

    colorWidgets->setLayout(colorWidgetLayout);
    vLayout->addWidget(colorWidgets);
    setLayout(vLayout);

    slider->attachColorChangeListener(*this);
    rightSelectedArea.setRect(selectedColorPanel->getScreenWidth() + 8, 9, rightPanelWidth, rightPanelHeight);
    rightPanelCircularButton.setCenter(rightSelectedArea.topRight());
    rightPanelCircularButton.setColor(QColor(255, 0, 0));

    std::vector<TextColorValueChangeManager *> textColorValueChangeManagers{hexColorGroupBox, rgbColorGroupBox, cmykColorGroupBox, hsvColorGroupBox, hslColorGroupBox};
    std::vector<TextColorValueListener *> textColorValueChangeListeners{hexColorGroupBox, rgbColorGroupBox, cmykColorGroupBox, hsvColorGroupBox, hslColorGroupBox, this};

    for(unsigned long long i = 0; i < textColorValueChangeManagers.size(); i++)
        for(unsigned long long j = 0; j < textColorValueChangeListeners.size(); j++){
            if(i != j){
                textColorValueChangeManagers[i]->attachTextColorChangeListener(*textColorValueChangeListeners[j]);
            }
        }

    slider->show();
    repaint();
}
void CentralWidget::updateLeftPanel(QPainter * painter){
    selectedColorPanel->paintPanel(painter);
}
void CentralWidget::updateRightPanel(QPainter * painter){
    QPen pen;
    QBrush brush;
    pen.setColor(Qt::blue);
    brush.setColor(*rightSelectedColor);
    brush.setStyle(Qt::SolidPattern);
    painter->setPen(pen);
    painter->setBrush(brush);

    QRect rect(rightSelectedArea);
    painter->fillRect(rect, brush);
    for(int x=rect.x(); x < rect.width() + rect.x(); x++){
        for(int y = rect.y(); y < rect.height() + rect.y(); y++){
            float value = ((rect.height() + rect.y() - y * 1.0) / rect.height()) * 255;
            float saturation = ((x - rect.x() * 1.0) / rect.width()) * 255;
            QPen pen;
            QColor col;
            col.setHsv(rightSelectedColor->hslHue(), (int)saturation, (int)value);
            pen.setColor(col);
            painter->setPen(pen);
            //            painter->setBrush(brush);

            painter->drawPoint(x, y);
        }
    }

    std::cout<<"Drawing filled rect"<<std::endl;
}
void CentralWidget::paintEvent(QPaintEvent * paintEvent){
    QPainter painter(this);
    updateLeftPanel(&painter);
    updateRightPanel(&painter);
    rightPanelCircularButton.drawCircle(&painter);
    std::cout<<"paintEvent CentralWidget"<<std::endl;
}

void CentralWidget::colorChanged(QColor & color){
    std::cout<<"This shouldn't be called"<<std::endl;
    const QPointF center = rightPanelCircularButton.getCenter();
    const float value = ((rightSelectedArea.height() + rightSelectedArea.y() - center.y() * 1.0) / rightSelectedArea.height()) * 255;
    const float saturation = ((center.x() - rightSelectedArea.x() * 1.0) / rightSelectedArea.width()) * 255;
    QColor _color;
    QColor rgbColor(color.red(), color.green(), color.blue());
    _color.setHsv(color.hue(), saturation, value);
    selectedColorPanel->setPanelColor(_color);
    rightSelectedColor->setRgb(rgbColor.red(), rgbColor.green(), rgbColor.blue());
    hexColorGroupBox->colorChanged(_color);
    rgbColorGroupBox->colorChanged(_color);
    cmykColorGroupBox->colorChanged(_color);
    hslColorGroupBox->colorChanged(_color);
    hsvColorGroupBox->colorChanged(_color);
    rightPanelCircularButton.setColor(_color);
    repaint();
}

void CentralWidget::mousePressEvent(QMouseEvent * event){
    std::cout<<"Mouse Press Event ****"<<std::endl;
    const int x = event->pos().x();
    const int y = event->pos().y();
    //    std::cout<<"x "<<x<<std::endl;
    //    std::cout<<"y "<<y<<std::endl;

    //    std::cout<<"x "<<event->pos().x()<<std::endl;
    //    std::cout<<"y "<<event->pos().y()<<std::endl;

    if(rightSelectedArea.contains(event->pos())){
        mouseClick = true;
        moveCircularButton(QPointF(x, y));
        repaint();
    }
    event->accept();
}

void CentralWidget::mouseMoveEvent(QMouseEvent * event){
    std::cout<<"Mouse Move Event ****"<<std::endl;
    const int x = event->pos().x();
    const int y = event->pos().y();

    if(mouseClick){
        int _x = std::min(std::max(rightSelectedArea.x(), x), rightSelectedArea.x() + rightSelectedArea.width());
        int _y = std::min(std::max(rightSelectedArea.y(), y), rightSelectedArea.y() + rightSelectedArea.height());

        moveCircularButton(QPointF(_x, _y));
        repaint();
    }
    event->accept();
}
void CentralWidget::mouseReleaseEvent(QMouseEvent * event){
    std::cout<<"Mouse Release Event ****"<<std::endl;
    mouseClick = false;
}

void CentralWidget::moveCircularButton(QPointF point){
    std::cout<<"Entering move circular button"<<std::endl;
    double x = point.x();
    double y = point.y();
    const float value = ((rightSelectedArea.height() + rightSelectedArea.y() - y * 1.0) / rightSelectedArea.height()) * 255;
    const float saturation = ((x - rightSelectedArea.x() * 1.0) / rightSelectedArea.width()) * 255;
    QColor col = slider->getCircularButtonColor();
    QColor color;
    color.setHsv(col.hue(), saturation, value);
    notifyColorChangeListener(color);
    rightPanelCircularButton.setColor(color);
    rightPanelCircularButton.setCenter(point);
    //    rightSelectedColor->setRgb(col.rgb());
    hexColorGroupBox->colorChanged(color);
    rgbColorGroupBox->colorChanged(color);
    cmykColorGroupBox->colorChanged(color);
    hslColorGroupBox->colorChanged(color);
    hsvColorGroupBox->colorChanged(color);
    selectedColorPanel->setPanelColor(color);
    std::cout<<"Exiting move circular Button"<<std::endl;
    //    repaint();
}

bool CentralWidget::attachColorChangeListener(ColorChangeListener & listener){
    if(std::find(colorChangeListeners.begin(),
                 colorChangeListeners.end(),
                 &listener) ==  colorChangeListeners.end()){
        colorChangeListeners.push_back(&listener);
        return true;
    }
    return false;
}
bool CentralWidget::detachColorChangeListener(ColorChangeListener & listener){
    if(std::find(colorChangeListeners.begin(),
                 colorChangeListeners.end(),
                 &listener) !=  colorChangeListeners.end()){
        for(auto i = colorChangeListeners.begin(); i != colorChangeListeners.end() ; ++i){
            if(*i == &listener){
                colorChangeListeners.erase(i);
                return true;
            }
        }
    }
    return false;
}
void CentralWidget::notifyColorChangeListener(QColor & color){
    for(auto i = colorChangeListeners.begin(); i != colorChangeListeners.end() ; ++i){
        (*i)->colorChanged(color);
    }
}

void CentralWidget::textColorValueChanged(QColor & color){
    std::cout<<"Here finally"<<color.name().toStdString()<<std::endl;
    //    rightSelectedColor->setRgb(color.rgb());
    selectedColorPanel->setPanelColor(color);
    slider->moveSliderTowardsColor(color);
    rightSelectedColor = new QColor(color.rgba());
    rightPanelCircularButton.setColor(color.rgba());
    QRect rect(rightSelectedArea);
    //    painter->fillRect(rect, brush);
    double closeness = std::numeric_limits<double>::max();
    auto getCloseness = [](double r1, double g1, double b1, double r2, double g2, double b2){
        return sqrt(pow(r1 - r2, 2) + pow(g1 - g2, 2) + pow(b1 - b2, 2));
    };
    int center_x = -1, center_y = -1;
    for(int x=rect.x(); x < rect.width() + rect.x(); x++){
        for(int y = rect.y(); y < rect.height() + rect.y(); y++){
            float value = ((rect.height() + rect.y() - y * 1.0) / rect.height()) * 255;
            float saturation = ((x - rect.x() * 1.0) / rect.width()) * 255;
            QPen pen;
            QColor col;
            col.setHsv(rightSelectedColor->hslHue(), (int)saturation, (int)value);
            double tempCloseness = getCloseness(col.red(), col.green(), col.blue(), color.red(), color.green(), color.blue());
            if(tempCloseness < closeness){
                closeness = tempCloseness;
                center_x = x;
                center_y = y;
            }
        }
    }
    if(center_x == -1 || center_y == -1){
        throw "Value error center_x or center_y is -1";
    }
    rightPanelCircularButton.setCenter(center_x, center_y);
    repaint();
}
