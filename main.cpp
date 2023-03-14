#include <QApplication>
#include "mainwindow.h"
#include <iostream>

void initializeWindow();

int main(int argc, char** argv){
    QApplication application(argc, argv);
    QPalette palette = application.palette();
    palette.setColor(QPalette::Window, Qt::white);
    application.setPalette(palette);

    MainWindow * mainWindow = new MainWindow();
    mainWindow->show();

    return application.exec();
}

//void initializeWindow(){

//    std::cout<<"Hello"<<std::endl;
//}
