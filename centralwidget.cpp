#include "centralwidget.h"
#include "hexcolorgroupbox.h"

#include <QVBoxLayout>
#include <Qt>
#include <QLabel>

CentralWidget::CentralWidget(QWidget *parent)
    : QWidget{parent}{
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
    colorWidgets->setFixedHeight(60);
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
//    slider->attachColorChangeListener(*hexColorGroupBox);
    rightSelectedArea.setRect(selectedColorPanel->getScreenWidth() + 8, 9, rightPanelWidth, rightPanelHeight);
    rightPanelCircularButton.setCenter(rightSelectedArea.topRight());
    rightPanelCircularButton.setColor(QColor(255, 0, 0));
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
    const QPointF center = rightPanelCircularButton.getCenter();
    const float value = ((rightSelectedArea.height() + rightSelectedArea.y() - center.y() * 1.0) / rightSelectedArea.height()) * 255;
    const float saturation = ((center.x() - rightSelectedArea.x() * 1.0) / rightSelectedArea.width()) * 255;
    QColor _color;
    _color.setHsv(color.hue(), saturation, value);
    selectedColorPanel->setPanelColor(_color);
    rightSelectedColor->setHsv(_color.hue(), _color.saturation(), _color.value());
    hexColorGroupBox->colorChanged(_color);
    rgbColorGroupBox->colorChanged(color);
    cmykColorGroupBox->colorChanged(color);
    hslColorGroupBox->colorChanged(color);
    hsvColorGroupBox->colorChanged(color);
//    selectedColorPanel->colorChanged(_color);
    rightPanelCircularButton.setColor(_color);
    repaint();
}

void CentralWidget::mousePressEvent(QMouseEvent * event){
    std::cout<<"Mouse Press Event ****"<<std::endl;
    const int x = event->x();
    const int y = event->y();

    if(rightSelectedArea.contains(event->pos())){
        mouseClick = true;
        moveCircularButton(QPointF(x, y));
        repaint();
    }
    event->accept();
}

void CentralWidget::mouseMoveEvent(QMouseEvent * event){
    std::cout<<"Mouse Move Event ****"<<std::endl;
    const int x = event->x();
    const int y = event->y();

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
    hexColorGroupBox->colorChanged(color);
    rgbColorGroupBox->colorChanged(color);
    cmykColorGroupBox->colorChanged(color);
    hslColorGroupBox->colorChanged(color);
    hsvColorGroupBox->colorChanged(color);
    selectedColorPanel->setPanelColor(color);
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
