#include "slider.h"

#include<QColor>

bool Slider::attachColorChangeListener(ColorChangeListener & listener){
    if(std::find(colorChangeListeners.begin(),
                 colorChangeListeners.end(),
                 &listener) ==  colorChangeListeners.end()){
        colorChangeListeners.push_back(&listener);
        return true;
    }
    return false;
}
bool Slider::detachColorChangeListener(ColorChangeListener & listener){
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
void Slider::notifyColorChangeListener(QColor & color){
    for(auto i = colorChangeListeners.begin(); i != colorChangeListeners.end() ; ++i){
        (*i)->colorChanged(color);
    }
}

Slider::Slider(QWidget *parent): QWidget{parent}{
    initializeSlider();

    for(int g = 0; g < 256 ; g++){
        std::vector<int>col{255, g, 0};
        colors.push_back(col);
    }
    for(int r = 255; r >=0 ; r--){
        std::vector<int>col{r, 255, 0};
        colors.push_back(col);
    }
    for(int b = 0; b < 256 ; b++){
        std::vector<int>col{0, 255, b};
        colors.push_back(col);
    }
    for(int g = 255; g >=0 ; g--){
        std::vector<int>col{0, g, 255};
        colors.push_back(col);
    }
    for(int r = 0; r < 256 ; r++){
        std::vector<int>col{r, 0, 255};
        colors.push_back(col);
    }
    for(int b = 255; b >= 0 ; b--){
        std::vector<int>col{255, 0, b};
        colors.push_back(col);
    }
}

void Slider::initializeSlider(){
    std::cout<<"Initializing Slider"<<std::endl;
    setFixedSize(windowWidth, windowHeight);

    circularButton.setColor(QColor(255, 0, 0));
    float x = (windowWidth - sliderWidth) / 2;
    float y = (windowHeight - sliderHeight) / 2 + sliderHeight / 2;
    circularButton.setCenter(x, y);

    repaint();
}

void Slider::paintEvent(QPaintEvent * event){

    std::cout<<"PaintEvent"<<std::endl;

    QPainter painter(this);
    painter.setPen(Qt::green);

    //    painter.drawRect(0, 0, windowWidth, windowHeight);
    //    painter.fillRect(0, 0, width(), height(), Qt::green);
    //    painter.setRenderHint(QPainter::Antialiasing);

    drawSlider(event, &painter);
    //    QRect rect(10, 20, 80, 60);
    //    painter.drawRoundedRect(rect, 25, 25);

    //    painter.drawRect(QRect(0, 0, 200, 100));
}
void Slider::drawSlider(QPaintEvent *event, QPainter * painter){
    int rectX = (windowWidth - sliderWidth) / 2;
    int rectY = (windowHeight - sliderHeight) / 2;
    QRect rect(rectX, rectY, sliderWidth - 1, sliderHeight - 1);

    painter->drawRect(rect);
    for(int x = 0; x < sliderWidth; x++){
        float val = x;
        float per = (val / sliderWidth);
        int index = std::min(std::max(int(colors.size() * per), 0) , (int)(colors.size() - 1));
        //        std::cout<<index<<std::endl;
        std::vector<int>col = colors[index];
        //        std::cout<<col[0]<<" "<<col[1]<<" "<<col[2]<<std::endl;
        QColor penColor(col[0], col[1], col[2]);
        QPen pen;
        pen.setColor(penColor);
        painter->setPen(pen);
        painter->drawLine(rectX + x, rectY, rectX + x, rectY + sliderHeight);
    }
    circularButton.drawCircle(painter);
    //    painter->drawRoundedRect(rect, 10, 10);
}

void Slider::mouseMoveEvent(QMouseEvent * event){
    std::cout<<"Mouse Move Event"<<std::endl;
    //    std::cout<<event->x()<<std::endl;
    //    std::cout<<event->y()<<std::endl;
    //    std::cout<<std::endl;
    const int x = event->pos().x();
    const int y = event->pos().y();
    if(mouseClick && x >= (windowWidth - sliderWidth) / 2 && x <= (windowWidth - sliderWidth) / 2 + sliderWidth){

        moveCircularButton(QPointF(x, y));
        repaint();
    }
    event->accept();

}

void Slider::mousePressEvent(QMouseEvent * event){
    std::cout<<"Mouse Press Event"<<std::endl;
    //    std::cout<<event->x()<<std::endl;
    //    std::cout<<event->y()<<std::endl;
    //    std::cout<<std::endl;

    const int x = event->pos().x();
    const int y = event->pos().y();

    if(x >= (windowWidth - sliderWidth) / 2 && x <= (windowWidth - sliderWidth) / 2 + sliderWidth &&
            y >= (windowHeight - sliderHeight) / 2 && y <= (windowHeight - sliderHeight) / 2 + sliderHeight){
        mouseClick = true;
        std::cout<<"Inside"<<std::endl;
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

void Slider::moveCircularButton(QPointF point){
    double _x = point.x();
    double _y = (windowHeight - sliderHeight) / 2 + sliderHeight / 2;
    double per = (_x - (windowWidth - sliderWidth) / 2) / sliderWidth;
    int index = std::min(std::max(int(colors.size() * per), 0) , (int)(colors.size() - 1));
    std::vector<int>col = colors[index];
    QColor _color;
    _color.setRgb(col[0], col[1], col[2]);
    circularButton.setCenter(QPointF(_x, _y));
    circularButton.setColor(_color);

    notifyColorChangeListener(_color);
    //    repaint();
}

void Slider::mouseReleaseEvent(QMouseEvent * event){
    mouseClick = false;
    std::cout<<"Mouse Release Event"<<std::endl;
}

QColor Slider::getCircularButtonColor(){
    return circularButton.getColor();
}

void Slider::moveSliderTowardsColor(QColor & color){

    auto findCloseness = [](long r1, long g1, long b1, long r2, long g2, long b2){
        return sqrt(pow(r1 - r2, 2) + pow(g1 - g2, 2) + pow(b1 - b2, 2));
    };
    const long red = color.red();
    const long green = color.green();
    const long blue = color.blue();
    int index = -1;
    long long closeness = LLONG_MAX;
    for(unsigned long long i = 0; i < colors.size(); i++){
        std::vector<int> & col = colors[i];
        const long r = col[0];
        const long g = col[1];
        const long b = col[2];
        if (index == -1){
            double close = findCloseness(r, g, b, red, green, blue);
            closeness = close;
            index = i;
        }else{
            double tempClose = findCloseness(r, g, b, red, green, blue);
            if(tempClose < closeness){
                closeness = tempClose;
                index = i;
            }
        }
    }
    if(index != -1){
        double per = (index + 1.0) / colors.size();
        double _y = (windowHeight - sliderHeight) / 2 + sliderHeight / 2;
        double _x = sliderWidth * per + (windowWidth - sliderWidth) / 2;
        std::vector<int>col = colors[index];
        QColor _color;
        _color.setRgb(col[0], col[1], col[2]);
        circularButton.setCenter(QPointF(_x, _y));
        circularButton.setColor(_color);
        repaint();
    }else{
        throw "Value error index is -1";
    }
}
