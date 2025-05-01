#include "mainwindow.h"
#include "loginwindow.h"
#include "catalogwindow.h"
#include "appcontroller.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    AppController controller;
    controller.start();


    return a.exec();
}
