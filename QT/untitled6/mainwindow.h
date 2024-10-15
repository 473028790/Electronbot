#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    std::string videoPath = "E:/Qt_program/666_rotated.mp4"; // 视频文件路径
    QString portName = "COM25"; // 串口名称
    int baudrate = 921600; // 波特率
    int frameSkip = 1; // 抽帧间隔
    std::vector<QByteArray> allFrames; // 存储帧数据
};
#endif // MAINWINDOW_H
