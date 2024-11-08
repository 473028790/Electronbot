#include "control.h"
#include "ui_control.h"

Control::Control(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Control)
{
    ui->setupUi(this);
    ui->lcdNumber_2->display(ui->horizontalSlider_2->value());
}

Control::~Control()
{
    delete ui;
}
extern int motor1_target_angle;
extern uint8_t paddingData[32];

void Control::on_horizontalSlider_2_valueChanged(int value)
{
    // 将滑块的整数值转换为浮点数
    float target_angle;
    motor1_target_angle=value;
    float new_target_angle = static_cast<float>(value);  // 假设我们需要0.0到1.0之间的浮点数
    target_angle = new_target_angle;
    ui->lcdNumber_2->display(target_angle);
    // 将浮点数转换为字节序列
    uint8_t *ptr = reinterpret_cast<uint8_t*>(&target_angle);

    // 将浮点数的字节序列复制到 paddingData 数组
    for (int i = 0; i < 4; ++i) {
        paddingData[i + 1] = ptr[i];
    }

    // 调试输出
    qDebug() << "头部舵机的目标角度:" << target_angle;
    //qDebug() << "paddingData[1-4]:";
    //for (int i = 1; i <= 4; ++i) {
    //    qDebug() << "paddingData[" << i << "] = " << static_cast<int>(paddingData[i]);
    //}
}

