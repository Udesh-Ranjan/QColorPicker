#include <QClipboard>
#include <QApplication>

#include "hexcolorgroupbox.h"

HexColorGroupBox::HexColorGroupBox(QWidget * parent):ColorGroupBox{parent}{
    setTitle("HEX");
    setAlignment(Qt::AlignCenter);
    getLineEdit()->setAlignment(Qt::AlignCenter);
    ColorChangeAction * colorChangeAction = new ColorChangeAction(*this);
    connect(getLineEdit(), &QLineEdit::textChanged, [colorChangeAction, this](){
        colorChangeAction->colorValueChanged(getLineEdit()->text());
    });
    QWidget * widget = new QWidget();
    widget->setFixedSize(25, 20);
    getLayout()->insertWidget(0, widget);
//    QIcon * icon = new QIcon("C:/Users/devpa/Pictures/icons/copy-outline-icon.png");
    QIcon * icon = new QIcon(":/icons/copy.png");
    copyButton->setIcon(*icon);
    copyButton->setFixedSize(25, 20);
    copyButton->setStyleSheet("QPushButton { border: 0px;}");
    copyButton->setIconSize(copyButton->size());
    copyButton->setCursor(QCursor(Qt::PointingHandCursor));
    QObject::connect(copyButton, &QPushButton::released, this, &HexColorGroupBox::copyButtonClicked);
    getLayout()->addWidget(copyButton, Qt::AlignRight);
}

void HexColorGroupBox::resetCopyButton(){
    copyButton->setIcon(QIcon(":/icons/copy.png"));
    copyFlag = true;
}

void HexColorGroupBox::copyButtonClicked(){
    if(copyFlag){
        clipboard->setText(getLineEdit()->text());
        copyButton->setIcon(QIcon(":/icons/tick.png"));
        std::cout<<"Copy Button clicked"<<std::endl;
        copyFlag = false;
    }
}

void HexColorGroupBox::colorChanged(QColor & color){
    std::cout<<"Hex Color Changed : "<<color.name().toStdString()<<std::endl;
    resetCopyButton();
    getLineEdit()->blockSignals(true);
    getLineEdit()->setText(color.name());
    getLineEdit()->blockSignals(false);
    std::cout<<"Hex Color Changed Exiting : "<<color.name().toStdString()<<std::endl;
}

HexColorGroupBox::ColorChangeAction::ColorChangeAction(HexColorGroupBox & hexColorGroupBox, QObject * parent):QObject{parent}{
    this->hexColorGroupBox = &hexColorGroupBox;
}

bool HexColorGroupBox::attachTextColorChangeListener(TextColorValueListener & listener){
    if(std::find(textColorValueListeners.begin(),
                 textColorValueListeners.end(),
                 &listener) ==  textColorValueListeners.end()){
        textColorValueListeners.push_back(&listener);
        return true;
    }
    return false;
}
bool HexColorGroupBox::detachTextColorChangeListener(TextColorValueListener & listener){
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
void HexColorGroupBox::notifyTextColorChangeListener(QColor & color){
    std::cout<<"Inside of notify Text Color Change Listener Hex"<<std::endl;
    for(auto i = textColorValueListeners.begin(); i != textColorValueListeners.end(); ++i){
        (*i)->textColorValueChanged(color);
    }
}

void HexColorGroupBox::ColorChangeAction::colorValueChanged(QString str){
    std::cout<<"XXXXXXXXXXXXXXXXXXX"<<std::endl;

    std::string colorValue = std::string(str.toStdString());
    if(colorValue.length() == 1)
        return;
    //    std::cout<<colorValue<<std::endl;
    //    std::cout<<colorValue.length()<<std::endl;
    std::transform(colorValue.begin(), colorValue.end(), colorValue.begin(), ::tolower);
    const char* typeOfWhitespaces = " \t\n\r\f\v";
    colorValue.erase(colorValue.find_last_not_of(typeOfWhitespaces) + 1);
    colorValue.erase(0, colorValue.find_first_not_of(typeOfWhitespaces));

    if((colorValue.length() == 4 || colorValue.length() == 7) && colorValue[0] == '#'){
        for(char ch : colorValue.substr(1)){
            if (!((ch >= 97 && ch <= 102) || (ch >= 48 && ch <= 57))){
                return;
            }
        }
    }else{
        return;
    }
    hexColorGroupBox->resetCopyButton();
    for(auto listener : hexColorGroupBox->textColorValueListeners){
        QColor color(colorValue.c_str());
        listener->textColorValueChanged(color);
    }
}

void HexColorGroupBox::textColorValueChanged(QColor & color){
    colorChanged(color);
}
