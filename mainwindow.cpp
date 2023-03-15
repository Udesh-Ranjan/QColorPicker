#include "mainwindow.h"
#include "centralwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}{
    initializeWindow();
}
void MainWindow::initializeWindow(){
    std::cout<<"Initializing"<<std::endl;
    setFixedSize(800, 600);
    CentralWidget * centralWidget = new CentralWidget();
    setCentralWidget(centralWidget);
    centralWidget->show();
}
