#include "expression.h"
#include "ui_expression.h"

extern std::string video_Path;


Expression::Expression(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Expression)
{
    ui->setupUi(this);
    thread_Send = new TDiceTHread(this);

    // 设置每个按钮的 backgroundImage 属性
    ui->pushButton_anger->setProperty("backgroundImage", ":/expression/build/Desktop_Qt_6_5_3_MinGW_64_bit-Debug/anger.png");
    ui->pushButton_disdain->setProperty("backgroundImage", ":/expression/build/Desktop_Qt_6_5_3_MinGW_64_bit-Debug/disdain.png");
    ui->pushButton_excited->setProperty("backgroundImage", ":/expression/build/Desktop_Qt_6_5_3_MinGW_64_bit-Debug/excited.png");
    ui->pushButton_fear->setProperty("backgroundImage", ":/expression/build/Desktop_Qt_6_5_3_MinGW_64_bit-Debug/fear.png");
    ui->pushButton_left->setProperty("backgroundImage", ":/expression/build/Desktop_Qt_6_5_3_MinGW_64_bit-Debug/left.png");
    ui->pushButton_normal->setProperty("backgroundImage", ":/expression/build/Desktop_Qt_6_5_3_MinGW_64_bit-Debug/normal.png");
    ui->pushButton_right->setProperty("backgroundImage", ":/expression/build/Desktop_Qt_6_5_3_MinGW_64_bit-Debug/right.png");
    ui->pushButton_sad->setProperty("backgroundImage", ":/expression/build/Desktop_Qt_6_5_3_MinGW_64_bit-Debug/sad.png");

    // 初始化按钮样式
    resetAllButtons();
}

Expression::~Expression()
{
    delete ui;
}

// 重置所有按钮的样式
QString Expression::getBaseStyle(const QString &imagePath) const
{
    return QString("QPushButton {"
                   "background-image: url(%1);"
                   "background-repeat: no-repeat;"
                   "background-position: center;"
                   "border: 5px solid transparent;"
                   "}").arg(imagePath);
}
void Expression::resetAllButtons()
{
    if (currentlySelectedButton) {
        qDebug() << "Resetting button:" << currentlySelectedButton->objectName();  // 打印当前选中的按钮
        currentlySelectedButton->setStyleSheet(getBaseStyle(currentlySelectedButton->property("backgroundImage").toString()));
        currentlySelectedButton = nullptr;
    }
}

void Expression::setButtonSelected(QPushButton *button)
{
    if (currentlySelectedButton && currentlySelectedButton != button) {
        currentlySelectedButton->setStyleSheet(getBaseStyle(currentlySelectedButton->property("backgroundImage").toString()));
    }

    QString selectedStyle = getBaseStyle(button->property("backgroundImage").toString());
    selectedStyle.replace("border: 5px solid transparent;", "border: 3px solid blue;");
    button->setStyleSheet(selectedStyle);
    currentlySelectedButton = button;

    qDebug() << "Selected button:" << button->objectName();  // 打印当前选中的按钮
}

void Expression::on_pushButton_anger_clicked()
{
    video_Path="E:/Qt_program/untitled6/build/Desktop_Qt_6_5_3_MinGW_64_bit-Debug/anger.mp4";
    if (currentlySelectedButton == ui->pushButton_anger) {
        resetAllButtons();
    } else {
        setButtonSelected(ui->pushButton_anger);
    }
}

void Expression::on_pushButton_disdain_clicked()
{
    video_Path="E:/Qt_program/untitled6/build/Desktop_Qt_6_5_3_MinGW_64_bit-Debug/disdain.mp4";
    if (currentlySelectedButton == ui->pushButton_disdain) {
        resetAllButtons();
    } else {
        setButtonSelected(ui->pushButton_disdain);
    }
}

void Expression::on_pushButton_excited_clicked()
{
    video_Path="E:/Qt_program/untitled6/build/Desktop_Qt_6_5_3_MinGW_64_bit-Debug/excited.mp4";
    if (currentlySelectedButton == ui->pushButton_excited) {
        resetAllButtons();
    } else {
        setButtonSelected(ui->pushButton_excited);
    }
}

void Expression::on_pushButton_fear_clicked()
{
    video_Path="E:/Qt_program/untitled6/build/Desktop_Qt_6_5_3_MinGW_64_bit-Debug/fear.mp4";
    if (currentlySelectedButton == ui->pushButton_fear) {
        resetAllButtons();
    } else {
        setButtonSelected(ui->pushButton_fear);
    }
}

void Expression::on_pushButton_left_clicked()
{
    video_Path="E:/Qt_program/untitled6/build/Desktop_Qt_6_5_3_MinGW_64_bit-Debug/left.mp4";
    if (currentlySelectedButton == ui->pushButton_left) {
        resetAllButtons();
    } else {
        setButtonSelected(ui->pushButton_left);
    }
}

void Expression::on_pushButton_normal_clicked()
{
    video_Path="E:/Qt_program/untitled6/build/Desktop_Qt_6_5_3_MinGW_64_bit-Debug/normal.mp4";
    if (currentlySelectedButton == ui->pushButton_normal) {
        resetAllButtons();
    } else {
        setButtonSelected(ui->pushButton_normal);
    }
}

void Expression::on_pushButton_right_clicked()
{
    video_Path="E:/Qt_program/untitled6/build/Desktop_Qt_6_5_3_MinGW_64_bit-Debug/right.mp4";
    if (currentlySelectedButton == ui->pushButton_right) {
        resetAllButtons();
    } else {
        setButtonSelected(ui->pushButton_right);
    }
}

void Expression::on_pushButton_sad_clicked()
{
    video_Path="E:/Qt_program/untitled6/build/Desktop_Qt_6_5_3_MinGW_64_bit-Debug/sad.mp4";
    if (currentlySelectedButton == ui->pushButton_sad) {
        resetAllButtons();
    } else {
        setButtonSelected(ui->pushButton_sad);
    }
}

void Expression::on_Button_start_clicked()
{
    thread_Send->start();
}

