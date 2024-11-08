#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "User_uart.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QByteArray>
#include <vector>
#include <QThread>
#include <opencv2/opencv.hpp>
#include <QCoreApplication>  // qApp 需要包含这个头文件

extern int motor1_target_angle;
extern int motor2_target_angle;
extern int motor3_target_angle;
extern int motor4_target_angle;
extern int motor5_target_angle;
extern int motor6_target_angle;
extern uint8_t paddingData[32];

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //thread_Send = new TDiceTHread(this);
    control = new Control(ui->widget);
    //control->hide();
    vision =new Vision(ui->widget);
    vision->hide();
    expression = new Expression(ui->widget);
    expression->hide();
    //connect(ui->menu,SIGNAL(aboutToShow()),this,SLOT(connectcontrol()));
    //connect(ui->menu_2,SIGNAL(aboutToShow()),this,SLOT(connectvision()));
    //connect(thread_Send,&TDiceTHread::startThread,this,&MainWindow::U_thread_Send_started);
    //connect(thread_Send,&TDiceTHread::finishThread,this,&MainWindow::U_thread_Send_finish);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 转换为18位真彩色
QByteArray convertTo18BitTrueColor(const cv::Mat &frame) {
    int width = frame.cols;
    int height = frame.rows;
    QByteArray byteArray;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // 获取像素的RGB值
            cv::Vec3b color = frame.at<cv::Vec3b>(y, x);
            uchar r = color[2];  // OpenCV存储为BGR
            uchar g = color[1];
            uchar b = color[0];

            // 转换为6位
            uchar r_6bit = (r >> 2) & 0x3F;
            uchar g_6bit = (g >> 2) & 0x3F;
            uchar b_6bit = (b >> 2) & 0x3F;

            // 转换为8位格式存储
            byteArray.append(r_6bit << 2);
            byteArray.append(g_6bit << 2);
            byteArray.append(b_6bit << 2);
        }
    }

    return byteArray;
}

// 处理视频，解析所有帧并存储到内存中
std::vector<QByteArray> processVideoAndStoreFrames(const std::string &videoPath, int frameSkip) {
    cv::VideoCapture videoCapture(videoPath);
    std::vector<QByteArray> allFrames;

    if (!videoCapture.isOpened()) {
        qDebug() << "Unable to open video file:" << QString::fromStdString(videoPath);
        return allFrames;
    }
    int frameCount = 0;
    int processedFrames = 0;
    // 如果frameSkip为0，我们假设用户想要处理每一帧
    if (frameSkip <= 0) {
        frameSkip = 1; // 设置为1表示不跳过帧
    }

    while (true) {
        cv::Mat frame;
        bool ret = videoCapture.read(frame);  // 读取一帧
        if (!ret) {
            break;
        }

        frameCount++;

        // 每隔frameSkip帧处理一次
        if (frameCount % frameSkip == 0) {
            processedFrames++;
            QByteArray byteArray = convertTo18BitTrueColor(frame);
            allFrames.push_back(byteArray);
        }
    }

    return allFrames;
}

/*
void MainWindow::on_pushButton_clicked()
{

    thread_Send->start();

}
*/



float target_angle;
/*
void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    // 将滑块的整数值转换为浮点数
    motor1_target_angle=value;
    float new_target_angle = static_cast<float>(value);  // 假设我们需要0.0到1.0之间的浮点数
    target_angle = new_target_angle+90;

    // 将浮点数转换为字节序列
    uint8_t *ptr = reinterpret_cast<uint8_t*>(&target_angle);

    // 将浮点数的字节序列复制到 paddingData 数组

    for (int i = 0; i < 4; ++i) {
        paddingData[i + 1] = ptr[i];
    }

    // 调试输出
    qDebug() << "新的目标角度:" << target_angle;
    qDebug() << "paddingData[1-4]:";
    for (int i = 1; i <= 4; ++i) {
        qDebug() << "paddingData[" << i << "] = " << static_cast<int>(paddingData[i]);
    }
}
*/
/*
void MainWindow::on_pushButton_10_clicked()
{
    if(paddingData[0]==0)
    {
        paddingData[0]=1;
        ui->pushButton_10->setText("全部失能");
    }
    else if(paddingData[0]==1)
    {
        paddingData[0]=0;
        ui->pushButton_10->setText("全部使能");
    }

}
*/




void MainWindow::on_Button_control_clicked()
{
    control->show();
    vision->hide();
    expression->hide();
}


void MainWindow::on_Button_vision_clicked()
{
    vision->show();
    control->hide();
    expression->hide();
}


void MainWindow::on_Button_Expression_clicked()
{
    vision->hide();
    control->hide();
    expression->show();
}

