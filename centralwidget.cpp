#include "centralwidget.h"
#include "selectedcolorpanel.h"

#include <QVBoxLayout>
#include <Qt>

CentralWidget::CentralWidget(QWidget *parent)
    : QWidget{parent}{
    QVBoxLayout * vLayout = new QVBoxLayout();
    SelectedColorPanel * selectedColorPanel = new SelectedColorPanel();
    Slider * slider = new Slider();
    vLayout->addWidget(selectedColorPanel);
    vLayout->addWidget(slider);
    setLayout(vLayout);

    slider->attachColorChangeListener(*selectedColorPanel);

    slider->show();
}
