#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMainWindow>
#include <QSerialPort>         // 添加这一行
#include <QSerialPortInfo>    // 如果需要使用串口信息
#include <QDebug>
#include <vector>             // 如果使用 std::vector
#include "tdicethread.h"
#include "control.h"
#include "vision.h"
#include "expression.h"

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //QSerialPort* initializeSerialPort(const QString &portName, int baudrate); // 函数声明，不需要额外限定

private slots:

    void on_Button_control_clicked();

    void on_Button_vision_clicked();

    void on_Button_Expression_clicked();

private:
    TDiceTHread *thread_Send;
    Ui::MainWindow *ui;
    Control* control;
    Vision * vision;
    Expression * expression;

    std::vector<QByteArray> allFrames; // 存储帧数据
};

std::vector<QByteArray> processVideoAndStoreFrames(const std::string &videoPath, int frameSkip);
void sendFramesOverSerial(QSerialPort *serial, const std::vector<QByteArray> &allFrames); // 函数声明
#endif // MAINWINDOW_H
