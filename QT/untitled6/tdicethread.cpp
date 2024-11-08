#include "tdicethread.h"
#include "mainwindow.h"

#include <QSerialPort>
#include <QSerialPortInfo>

int motor1_target_angle;
int motor2_target_angle;
int motor3_target_angle;
int motor4_target_angle;
int motor5_target_angle;
int motor6_target_angle;
extern QSerialPort *serial;


//初始化串口
QSerialPort *serial = new QSerialPort();
QSerialPort* TDiceTHread::initializeSerialPort(const QString &portName, int baudrate) {
    //QSerialPort *serial = new QSerialPort(this);
    serial->setPortName(portName);
    serial->setBaudRate(baudrate);

    if (!serial->open(QIODevice::ReadWrite)) {
        qDebug() << "Unable to open serial port" << portName;
        delete serial; // 打开失败时，释放内存
        return nullptr;
    }
    // 连接 readyRead 信号到 handleReadyRead 槽
    connect(serial, &QSerialPort::readyRead, this, &TDiceTHread::handleReadyRead);

    return serial; // 返回成功打开的串口指针
}
// 接收串口数据的槽函数

void TDiceTHread::handleReadyRead() {
    if (serial && serial->bytesAvailable() >= 32) { // 确保读取至少32字节的数据
        QByteArray data = serial->read(32); // 读取32字节
        // qDebug() << "Received data:" << data.toHex(); // 输出接收到的数据，方便调试

        if (data.size() >= 5) { // 确保至少有5个字节可用
            // 提取第2到第5个字节
            QByteArray floatBytes = data.mid(1, 4); // 从索引1开始，提取4个字节（第2到第5个字节）
            //QByteArray floatBytes3 = data.mid(5, 8); // 从索引1开始，提取4个字节（第2到第5个字节）
            QByteArray floatBytes3 = data.mid(9, 12); // 从索引1开始，提取4个字节（第2到第5个字节）
            // 将字节转换为 float
            float value;
            float value3;
            memcpy(&value, floatBytes.constData(), sizeof(float)); // 使用 memcpy 将字节数据拷贝到 float 类型
            memcpy(&value3, floatBytes3.constData(), sizeof(float)); // 使用 memcpy 将字节数据拷贝到 float 类型
            // 输出转换后的浮点值
            qDebug() << "Extracted float value:" << value3;

            // 你可以在这里对这个浮点值进行进一步处理
        }
    }
}

//发送串口
uint8_t paddingData[32];

void sendFramesOverSerial(QSerialPort *serial, const std::vector<QByteArray> &allFrames) {
    if (!serial) {
        qDebug() << "Serial port is not initialized!";
        return;
    }

    if (!serial->isOpen() && !serial->open(QIODevice::ReadWrite)) {
        qDebug() << "Failed to open serial port!";
        return;
    }
    for (int i = 0; i < allFrames.size(); ++i) {
        QByteArray frameData = allFrames[i];

        int quarterSize = frameData.size() / 4;
        for (int part = 0; part < 4; ++part) {
            int startIndex = part * quarterSize;
            int endIndex = (part < 3) ? startIndex + quarterSize : frameData.size();
            QByteArray chunk = frameData.mid(startIndex, endIndex - startIndex);
            QByteArray totalData;

            totalData = chunk;
            totalData.append(reinterpret_cast<char*>(paddingData), 32);

            qint64 bytesWritten = serial->write(totalData);

            if (!serial->waitForBytesWritten(50)) {
                qDebug() << "Failed to write data to serial port!";
            }

            QThread::msleep(10);  // 添加延迟
        }
    }

    serial->close();
}



TDiceTHread::TDiceTHread(QObject *parent): QThread{parent}
{
}

// 视频文件路径
std::string video_Path = "E:/Qt_program/untitled6/build/Desktop_Qt_6_5_3_MinGW_64_bit-Debug/666_rotated.mp4";

std::vector<QByteArray> allFrames;

void TDiceTHread::run()
{

    serial = TDiceTHread::initializeSerialPort(portName, baudrate);
    U_stop=false;

    while(!U_stop)
    {
        // 设置抽帧间隔
        int frameSkip =1;
        qDebug() << "Video Path:" << video_Path;
        allFrames = processVideoAndStoreFrames(video_Path, frameSkip);

        if (!allFrames.empty()) {
            for (int i = 0; i < 1; ++i) {  // 循环发送5次
                sendFramesOverSerial(serial, allFrames);
            }
        }
        U_stop=true;

    }
    quit();

}

