#include "mainwindow.h"

#include <QApplication>
#include <QMainWindow>
#include<QWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;
    window.setWindowTitle("MyTodoList");

    window.show();
    return a.exec();
}
