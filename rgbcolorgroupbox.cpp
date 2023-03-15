#include "rgbcolorgroupbox.h"

RgbColorGroupBox::RgbColorGroupBox(){
    setTitle("RGB");
    ColorChangeAction * colorChangeAction = new ColorChangeAction(*this);
    connect(getLineEdit(), &QLineEdit::textChanged, [colorChangeAction, this](){
        colorChangeAction->colorValueChanged(getLineEdit()->text());
    });
}

void RgbColorGroupBox::colorChanged(QColor & color){
    std::cout<<"Entering rgb color changed"<<std::endl;
    getLineEdit()->blockSignals(true);
    getLineEdit()->setText(QString::fromStdString(std::to_string(color.red()) + ", " + std::to_string(color.green()) + ", " + std::to_string(color.blue())));
    getLineEdit()->blockSignals(false);
    std::cout<<"Exiting rgb color changed"<<std::endl;
}

RgbColorGroupBox::ColorChangeAction::ColorChangeAction(RgbColorGroupBox & rgbColorGroupBox, QObject * parent):QObject{parent}{
    this->rgbColorGroupBox = &rgbColorGroupBox;
}

bool RgbColorGroupBox::attachTextColorChangeListener(TextColorValueListener & listener){
    if(std::find(textColorValueListeners.begin(),
                 textColorValueListeners.end(),
                 &listener) ==  textColorValueListeners.end()){
        textColorValueListeners.push_back(&listener);
        return true;
    }
    return false;
}
bool RgbColorGroupBox::detachTextColorChangeListener(TextColorValueListener & listener){
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
void RgbColorGroupBox::notifyTextColorChangeListener(QColor & color){
    for(auto i = textColorValueListeners.begin(); i != textColorValueListeners.end(); ++i){
        (*i)->textColorValueChanged(color);
    }
}

void RgbColorGroupBox::ColorChangeAction::colorValueChanged(QString str){
    std::cout<<"RGBXXXXXXXXXXXXXXXXXXX"<<std::endl;

    std::string colorValue = std::string(str.toStdString());
    //    if(colorValue.length() == 1)
    //        return;
    //    std::cout<<colorValue<<std::endl;
    //    std::cout<<colorValue.length()<<std::endl;
    std::regex r("\\s+");
    colorValue = std::regex_replace(colorValue, r, "");
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
            if(val < 0 || val > 255)
                return;
        }
    }else{
        return;
    }
    const int red = std::atoi(vec[0].c_str());
    const int green = std::atoi(vec[1].c_str());
    const int blue = std::atoi(vec[2].c_str());

    for(auto listener : rgbColorGroupBox->textColorValueListeners){
        QColor color(red, green, blue);
        listener->textColorValueChanged(color);
    }
}
void RgbColorGroupBox::textColorValueChanged(QColor & color){
    colorChanged(color);
}
