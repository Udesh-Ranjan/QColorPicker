#include "mainwindow.h"
#include <iostream>
#include "centralwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}{
    initializeWindow();
}
void MainWindow::initializeWindow(){
    std::cout<<"Initializing"<<std::endl;
    setFixedSize(700, 500);
    CentralWidget * centralWidget = new CentralWidget();
    setCentralWidget(centralWidget);
    centralWidget->show();
}
