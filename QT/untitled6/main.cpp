#include "mainwindow.h"

#include <QApplication>

#include <opencv2/opencv.hpp>
#include <QSerialPort>
#include <QDebug>
#include <QByteArray>
#include <vector>
#include <QThread>

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
std::vector<QByteArray> processVideoAndStoreFrames(const std::string &videoPath, int frameSkip = 5) {
    cv::VideoCapture videoCapture(videoPath);
    std::vector<QByteArray> allFrames;

    if (!videoCapture.isOpened()) {
        qDebug() << "Unable to open video file:" << QString::fromStdString(videoPath);
        return allFrames;
    }

    int frameCount = 0;
    int processedFrames = 0;

    while (true) {
        cv::Mat frame;
        bool ret = videoCapture.read(frame);  // 读取一帧
        if (!ret) {
            qDebug() << "End of video reached";
            break;
        }

        frameCount++;

        // 每隔frameSkip帧处理一次
        if (frameCount % frameSkip == 0) {
            processedFrames++;
            qDebug() << "Processing frame" << frameCount << "(skipping frames), processed frame count:" << processedFrames;

            // 将帧转换为18位真彩色，并存储字节数组
            QByteArray byteArray = convertTo18BitTrueColor(frame);
            allFrames.push_back(byteArray);
        }
    }

    qDebug() << "Video processing complete, total frames:" << frameCount << ", processed frames:" << processedFrames;
    return allFrames;
}

// 通过串口发送所有帧数据
void sendFramesOverSerial(const std::vector<QByteArray> &allFrames, const QString &portName, int baudrate = 115200) {
    QSerialPort serial;
    serial.setPortName(portName);
    serial.setBaudRate(baudrate);

    if (!serial.open(QIODevice::WriteOnly)) {
        qDebug() << "Unable to open serial port" << portName;
        return;
    }

    for (int i = 0; i < allFrames.size(); ++i) {
        QByteArray frameData = allFrames[i];
        qDebug() << "Sending frame" << i + 1 << "with" << frameData.size() << "bytes";

        int quarterSize = frameData.size() / 4;
        for (int part = 0; part < 4; ++part) {
            int startIndex = part * quarterSize;
            int endIndex = (part < 3) ? startIndex + quarterSize : frameData.size();
            QByteArray chunk = frameData.mid(startIndex, endIndex - startIndex);
            QByteArray totalData;

            // 判断是否需要补齐512字节
            if (chunk.size() % 512 != 0) {
                totalData = chunk;
                totalData.append(QByteArray(32, '\0'));  // 添加32字节调试数据
                qDebug() << "Added" << chunk.size() << "bytes and 32 bytes of debug data, sending" << totalData.size() << "bytes";
            } else {
                int bytesSent = 0;
                while (bytesSent < chunk.size()) {
                    QByteArray packet = chunk.mid(bytesSent, 512);
                    totalData.append(packet);
                    bytesSent += packet.size();
                    qDebug() << "Sent" << packet.size() << "bytes, total sent" << bytesSent << "/" << chunk.size() << "bytes";
                }
                totalData.append(QByteArray(32, '\0'));  // 添加32字节调试数据
            }

            // 发送数据，并等待写入完成
            qint64 bytesWritten = serial.write(totalData);
            if (!serial.waitForBytesWritten(1000)) {
                qDebug() << "Failed to write data to serial port!";
            } else {
                qDebug() << "Successfully wrote" << bytesWritten << "bytes to serial port";
            }

            QThread::msleep(50);  // 添加延迟
        }
    }

    serial.close();
    qDebug() << "All frames sent successfully";
}

int main(int argc, char *argv[])
{
    // 视频文件路径
    std::string videoPath = "E:/Qt_program/666_rotated.mp4";
    // 串口配置
    QString portName = "COM25";
    int baudrate = 921600;

    // 设置抽帧间隔
    int frameSkip = 2;

    // 第一步：处理视频并存储所有帧的字节数组
    std::vector<QByteArray> allFrames = processVideoAndStoreFrames(videoPath, frameSkip);

    // 第二步：通过串口逐帧发送所有已处理的帧
    if (!allFrames.empty()) {
        sendFramesOverSerial(allFrames, portName, baudrate);
    }

    return 0;
}
