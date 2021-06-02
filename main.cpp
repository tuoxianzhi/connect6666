#include "mainwindow.h"
#include <QApplication>
int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Connect 6");
    return a.exec();
}
