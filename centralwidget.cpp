#include "centralwidget.h"


#include <QVBoxLayout>
#include <Qt>

CentralWidget::CentralWidget(QWidget *parent)
    : QWidget{parent}{
    setFixedSize(700, 500);
    QVBoxLayout * vLayout = new QVBoxLayout();

    vLayout->addWidget(selectedColorPanel);
    vLayout->addWidget(slider);
    setLayout(vLayout);

    slider->attachColorChangeListener(*selectedColorPanel);
    slider->attachColorChangeListener(*this);
    rightSelectedArea.setRect(selectedColorPanel->getScreenWidth() + 8, 9, rightPanelWidth, rightPanelHeight);
    rightPanelCircularButton.setCenter(rightSelectedArea.topRight());
    rightPanelCircularButton.setColor(QColor(255, 0, 0));
    attachColorChangeListener(*selectedColorPanel);
//    for(int x=rightSelectedArea.x(); x < rightSelectedArea.width() + rightSelectedArea.x(); x++){
//        for(int y = rightSelectedArea.y(); y < rightSelectedArea.height() + rightSelectedArea.y(); y++){
//            float value = ((rightSelectedArea.height() + rightSelectedArea.y() - y * 1.0) / rightSelectedArea.height()) * 255;
//            float saturation = ((x - rightSelectedArea.x() * 1.0) / rightSelectedArea.width()) * 255;
//            saturationValueVector.push_back(new std::vector<int>{(int)saturation, (int)value});
//        }
//    }
    slider->show();
    repaint();
}
void CentralWidget::updateRightPanel(QPainter * painter){
    QPen pen;
    QBrush brush;
    pen.setColor(Qt::blue);
    brush.setColor(*rightSelectedColor);
    brush.setStyle(Qt::SolidPattern);
    painter->setPen(pen);
    painter->setBrush(brush);

    QRect rect(selectedColorPanel->getScreenWidth() + 8, 9, rightPanelWidth, rightPanelHeight);
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
    updateRightPanel(&painter);
    rightPanelCircularButton.drawCircle(&painter);
    std::cout<<"paintEvent CentralWidget"<<std::endl;
}

void CentralWidget::colorChanged(QColor & color){
    rightSelectedColor->setRgb(color.rgb());
    repaint();
}

void CentralWidget::mousePressEvent(QMouseEvent * event){
    std::cout<<"Mouse Press Event ****"<<std::endl;
    const int x = event->x();
    const int y = event->y();

    if(rightSelectedArea.contains(event->pos())){
        mouseClick = true;
        std::cout<<"Gotcha **********"<<std::endl;
        //        float _x = event->x();
        //        float _y = (windowHeight - sliderHeight) / 2 + sliderHeight / 2;
        //        float per = (_x - (windowWidth - sliderWidth) / 2) / sliderWidth;
        //        int index = std::min(std::max(int(colors.size() * per), 0) , (int)(colors.size() - 1));
        //        std::vector<int>col = colors[index];
        //        QColor _color;
        //        _color.setRgb(col[0], col[1], col[2]);
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
        std::cout<<"Gotcha **********"<<std::endl;
        //        float _x = event->x();
        //        float _y = (windowHeight - sliderHeight) / 2 + sliderHeight / 2;
        //        float per = (_x - (windowWidth - sliderWidth) / 2) / sliderWidth;
        //        int index = std::min(std::max(int(colors.size() * per), 0) , (int)(colors.size() - 1));
        //        std::vector<int>col = colors[index];
        //        QColor _color;
        //        _color.setRgb(col[0], col[1], col[2]);
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
//    double _x = point.x();
//    double _y = (windowHeight - sliderHeight) / 2 + sliderHeight / 2;
//    double per = (_x - (windowWidth - sliderWidth) / 2) / sliderWidth;
//    int index = std::min(std::max(int(colors.size() * per), 0) , (int)(colors.size() - 1));
//    std::vector<int>col = colors[index];
//    QColor _color;
//    _color.setRgb(col[0], col[1], col[2]);
    double x = point.x();
    double y = point.y();
    const float value = ((rightSelectedArea.height() + rightSelectedArea.y() - y * 1.0) / rightSelectedArea.height()) * 255;
    const float saturation = ((x - rightSelectedArea.x() * 1.0) / rightSelectedArea.width()) * 255;
    QColor col = slider->getCircularButtonColor();
    QColor color;
    color.setHsv(col.hue(), saturation, value);
    notifyColorChangeListener(color);
    rightPanelCircularButton.setCenter(point);
//    circularButton.setColor(_color);

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
