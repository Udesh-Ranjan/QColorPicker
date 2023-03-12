#include <QApplication>
#include "mainwindow.h"
#include <iostream>

void initializeWindow();

int main(int argc, char** argv){
    QApplication application(argc, argv);

    MainWindow * mainWindow = new MainWindow();
    mainWindow->show();

    return application.exec();
}

//void initializeWindow(){

//    std::cout<<"Hello"<<std::endl;
//}
