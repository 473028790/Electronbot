#ifndef TDICETHREAD_H
#define TDICETHREAD_H

#include <QObject>
#include <QThread>
#include <QSerialPort>
#include <QSerialPortInfo>

class TDiceTHread : public QThread
{
    Q_OBJECT
private:
    bool motor_Enable;
    bool U_stop=false;
    QString portName = "COM29"; // 串口名称
    int baudrate = 921600; // 波特率
    int frameSkip = 1; // 抽帧间隔

private slots:
    void handleReadyRead(); // 接收串口数据的槽函数
protected:
    void run();
public:
    void startThread();
    explicit TDiceTHread(QObject *parent = nullptr);
    QSerialPort* initializeSerialPort(const QString &portName, int baudrate); // 函数声明，不需要额外限定
signals:
    void new_motor_angle(int motor_id,int angle);
};

#endif // TDICETHREAD_H
