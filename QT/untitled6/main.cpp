#include "mainwindow.h"

#include <QApplication>

#include <opencv2/opencv.hpp>
#include <QSerialPort>
#include <QDebug>
#include <QByteArray>
#include <vector>
#include <QThread>
#include "User_uart.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();

}
