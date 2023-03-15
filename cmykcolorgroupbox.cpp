#include "cmykcolorgroupbox.h"

CmykColorGroupBox::CmykColorGroupBox(){
    setTitle("CMYK");
    ColorChangeAction * colorChangeAction = new ColorChangeAction(*this);
    connect(getLineEdit(), &QLineEdit::textChanged, [colorChangeAction, this](){
        colorChangeAction->colorValueChanged(getLineEdit()->text());
    });
}

void CmykColorGroupBox::colorChanged(QColor & color){
    std::cout<<"Entering cmyk color changed"<<std::endl;
    int c = int(color.cyan() * 100.0 / 255.0);
    int m = int(color.magenta() * 100.0 / 255.0);
    int y = int(color.yellow() * 100.0 / 255.0);
    int k = int(color.black() * 100.0 / 255.0);

    getLineEdit()->blockSignals(true);
    getLineEdit()->setText(QString::fromStdString(
                               std::to_string(c) + "%, " +
                               std::to_string(m) + "%, " +
                               std::to_string(y) + "%, " +
                               std::to_string(k) + "%"));
    getLineEdit()->blockSignals(false);
    std::cout<<"Exiting cmyk color changed"<<std::endl;
}

CmykColorGroupBox::ColorChangeAction::ColorChangeAction(CmykColorGroupBox & cmykColorGroupBox, QObject * parent):QObject{parent}{
    this->cmykColorGroupBox = &cmykColorGroupBox;
}

bool CmykColorGroupBox::attachTextColorChangeListener(TextColorValueListener & listener){
    if(std::find(textColorValueListeners.begin(),
                 textColorValueListeners.end(),
                 &listener) ==  textColorValueListeners.end()){
        textColorValueListeners.push_back(&listener);
        return true;
    }
    return false;
}
bool CmykColorGroupBox::detachTextColorChangeListener(TextColorValueListener & listener){
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
void CmykColorGroupBox::notifyTextColorChangeListener(QColor & color){
    for(auto i = textColorValueListeners.begin(); i != textColorValueListeners.end(); ++i){
        (*i)->textColorValueChanged(color);
    }
}

void CmykColorGroupBox::ColorChangeAction::colorValueChanged(QString str){
    std::cout<<"XXXXXXXXXXXXXXXXXXX"<<std::endl;

    std::string colorValue = std::string(str.toStdString());

    std::regex r("\\s+");
    colorValue = std::regex_replace(colorValue, r, "");
    std::regex r_per("%");
    colorValue = std::regex_replace(colorValue, r_per, "");

    std::regex _r(",");
    std::vector<std::string> vec(std::sregex_token_iterator(
                                     colorValue.begin(), colorValue.end(), _r, -1),
                                 std::sregex_token_iterator());

    if(vec.size() == 4){
        for(std::string & str : vec){
            char * p;
            strtol(str.c_str(), &p, 10);
            if(*p != 0)
                return;
            std::cout<<str<<std::endl;
            long long val = std::atol(str.c_str());
            if(val < 0 || val > 100)
                return;
        }
    }else{
        return;
    }
    const int cyan = (std::atoi(vec[0].c_str()) / 100.0) * 255 ;
    const int magenta = (std::atoi(vec[1].c_str()) / 100.0) * 255;
    const int yellow = (std::atoi(vec[2].c_str()) / 100.0) * 255;
    const int black = (std::atoi(vec[3].c_str()) / 100.0) * 255;

    for(auto listener : cmykColorGroupBox->textColorValueListeners){
        QColor color;
        color.setCmyk(cyan, magenta, yellow, black);
        listener->textColorValueChanged(color);
    }
}

void CmykColorGroupBox::textColorValueChanged(QColor & color){
    colorChanged(color);
}
