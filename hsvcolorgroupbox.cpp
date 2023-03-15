#include "hsvcolorgroupbox.h"

HsvColorGroupBox::HsvColorGroupBox(){
    setTitle("HSV");
    ColorChangeAction * colorChangeAction = new ColorChangeAction(*this);
    connect(getLineEdit(), &QLineEdit::textChanged, [colorChangeAction, this](){
        colorChangeAction->colorValueChanged(getLineEdit()->text());
    });
}

void HsvColorGroupBox::colorChanged(QColor & color){
    std::cout<<"Entering hsv color changed"<<std::endl;
    int hue = color.hue();
    int saturation = std::max(
                std::min(int(color.saturation() * 100.0 / 255.0 + .5), 100), 0);
    int value = std::max(
                std::min(int(color.value() * 100.0 / 255.0 + .5), 100), 0);

    getLineEdit()->blockSignals(true);
    getLineEdit()->setText(
                QString::fromStdString(
                    std::to_string(hue) + "°, " +
                    std::to_string(saturation) + "%, " +
                    std::to_string(value) + "%"));
    getLineEdit()->blockSignals(false);
    std::cout<<"Entering hsv color changed"<<std::endl;
}


HsvColorGroupBox::ColorChangeAction::ColorChangeAction(HsvColorGroupBox & hsvColorGroupBox, QObject * parent):QObject{parent}{
    this->hsvColorGroupBox = &hsvColorGroupBox;
}

bool HsvColorGroupBox::attachTextColorChangeListener(TextColorValueListener & listener){
    if(std::find(textColorValueListeners.begin(),
                 textColorValueListeners.end(),
                 &listener) ==  textColorValueListeners.end()){
        textColorValueListeners.push_back(&listener);
        return true;
    }
    return false;
}
bool HsvColorGroupBox::detachTextColorChangeListener(TextColorValueListener & listener){
    if(std::find(textColorValueListeners.begin(),
                 textColorValueListeners.end(),
                 &listener) !=  textColorValueListeners.end()){
        textColorValueListeners.push_back(&listener);
        for(auto i = textColorValueListeners.begin(); i != textColorValueListeners.end() ; ++i){
            if(*i == &listener){
                textColorValueListeners.erase(i);
                return true;
            }
        }
    }
    return false;
}
void HsvColorGroupBox::notifyTextColorChangeListener(QColor & color){
    for(auto i = textColorValueListeners.begin(); i != textColorValueListeners.end(); ++i){
        (*i)->textColorValueChanged(color);
    }
}

void HsvColorGroupBox::ColorChangeAction::colorValueChanged(QString str){
    std::cout<<"XXXXXXXXXXXXXXXXXXX"<<std::endl;

    std::string colorValue = std::string(str.toStdString());
    //    if(colorValue.length() == 1)
    //        return;
    //    std::cout<<colorValue<<std::endl;
    //    std::cout<<colorValue.length()<<std::endl;
    std::regex r("\\s+");
    colorValue = std::regex_replace(colorValue, r, "");
    std::regex r_deg("°");
    colorValue = std::regex_replace(colorValue, r_deg, "");
    std::regex r_per("%");
    colorValue = std::regex_replace(colorValue, r_per, "");
    std::regex _r(",");

    std::vector<std::string> vec(std::sregex_token_iterator(
                                     colorValue.begin(), colorValue.end(), _r, -1),
                                 std::sregex_token_iterator());

    if(vec.size() == 3){
        for(std::string & str : vec){
            char * p;
            strtol(str.c_str(), &p, 10);
            if(*p != 0)
                return;
            std::cout<<str<<std::endl;
            long long val = std::atol(str.c_str());
            if(val < 0 || val > 360)
                return;
        }
    }else{
        return;
    }
    const int hue = std::atoi(vec[0].c_str());
    const int saturation = std::atoi(vec[1].c_str());
    const int value = std::atoi(vec[2].c_str());

    if(saturation > 100 || value > 100)
        return;

    for(auto listener : hsvColorGroupBox->textColorValueListeners){
        QColor color;
        color.setHsv(hue, (saturation / 100.0) * 255.0 , (value / 100.0) * 255.0);
        listener->textColorValueChanged(color);
    }
}

void HsvColorGroupBox::textColorValueChanged(QColor & color){
    colorChanged(color);
}
