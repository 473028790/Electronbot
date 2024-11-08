/********************************************************************************
** Form generated from reading UI file 'control.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTROL_H
#define UI_CONTROL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Control
{
public:
    QSlider *horizontalSlider;
    QLabel *label;
    QSlider *horizontalSlider_2;
    QLabel *label_2;
    QSlider *horizontalSlider_3;
    QLabel *label_3;
    QSlider *horizontalSlider_4;
    QLabel *label_4;
    QSlider *horizontalSlider_5;
    QLabel *label_5;
    QSlider *horizontalSlider_6;
    QLabel *label_6;
    QLCDNumber *lcdNumber;
    QLCDNumber *lcdNumber_2;
    QLCDNumber *lcdNumber_3;
    QLCDNumber *lcdNumber_4;
    QLCDNumber *lcdNumber_5;
    QLCDNumber *lcdNumber_6;
    QLabel *label_7;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QLabel *label_8;

    void setupUi(QWidget *Control)
    {
        if (Control->objectName().isEmpty())
            Control->setObjectName("Control");
        Control->resize(780, 650);
        horizontalSlider = new QSlider(Control);
        horizontalSlider->setObjectName("horizontalSlider");
        horizontalSlider->setGeometry(QRect(420, 45, 291, 15));
        horizontalSlider->setMinimum(0);
        horizontalSlider->setMaximum(180);
        horizontalSlider->setValue(90);
        horizontalSlider->setOrientation(Qt::Horizontal);
        label = new QLabel(Control);
        label->setObjectName("label");
        label->setGeometry(QRect(420, 15, 91, 41));
        QFont font;
        font.setPointSize(15);
        label->setFont(font);
        label->setLineWidth(1);
        horizontalSlider_2 = new QSlider(Control);
        horizontalSlider_2->setObjectName("horizontalSlider_2");
        horizontalSlider_2->setGeometry(QRect(420, 90, 291, 15));
        horizontalSlider_2->setMinimum(0);
        horizontalSlider_2->setMaximum(180);
        horizontalSlider_2->setValue(90);
        horizontalSlider_2->setTracking(true);
        horizontalSlider_2->setOrientation(Qt::Horizontal);
        label_2 = new QLabel(Control);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(420, 60, 91, 41));
        label_2->setFont(font);
        label_2->setLineWidth(1);
        horizontalSlider_3 = new QSlider(Control);
        horizontalSlider_3->setObjectName("horizontalSlider_3");
        horizontalSlider_3->setGeometry(QRect(420, 135, 291, 15));
        horizontalSlider_3->setMinimum(0);
        horizontalSlider_3->setMaximum(180);
        horizontalSlider_3->setValue(90);
        horizontalSlider_3->setOrientation(Qt::Horizontal);
        label_3 = new QLabel(Control);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(420, 105, 91, 41));
        label_3->setFont(font);
        label_3->setLineWidth(1);
        horizontalSlider_4 = new QSlider(Control);
        horizontalSlider_4->setObjectName("horizontalSlider_4");
        horizontalSlider_4->setGeometry(QRect(420, 180, 291, 16));
        horizontalSlider_4->setMinimum(0);
        horizontalSlider_4->setMaximum(180);
        horizontalSlider_4->setValue(90);
        horizontalSlider_4->setOrientation(Qt::Horizontal);
        label_4 = new QLabel(Control);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(420, 150, 91, 41));
        label_4->setFont(font);
        label_4->setLineWidth(1);
        horizontalSlider_5 = new QSlider(Control);
        horizontalSlider_5->setObjectName("horizontalSlider_5");
        horizontalSlider_5->setGeometry(QRect(420, 225, 291, 16));
        horizontalSlider_5->setMinimum(0);
        horizontalSlider_5->setMaximum(180);
        horizontalSlider_5->setValue(90);
        horizontalSlider_5->setOrientation(Qt::Horizontal);
        label_5 = new QLabel(Control);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(420, 195, 91, 41));
        label_5->setFont(font);
        label_5->setLineWidth(1);
        horizontalSlider_6 = new QSlider(Control);
        horizontalSlider_6->setObjectName("horizontalSlider_6");
        horizontalSlider_6->setGeometry(QRect(420, 270, 291, 16));
        horizontalSlider_6->setMinimum(0);
        horizontalSlider_6->setMaximum(180);
        horizontalSlider_6->setValue(90);
        horizontalSlider_6->setOrientation(Qt::Horizontal);
        label_6 = new QLabel(Control);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(420, 240, 91, 41));
        label_6->setFont(font);
        label_6->setLineWidth(1);
        lcdNumber = new QLCDNumber(Control);
        lcdNumber->setObjectName("lcdNumber");
        lcdNumber->setGeometry(QRect(640, 23, 64, 23));
        lcdNumber_2 = new QLCDNumber(Control);
        lcdNumber_2->setObjectName("lcdNumber_2");
        lcdNumber_2->setGeometry(QRect(640, 70, 64, 23));
        lcdNumber_3 = new QLCDNumber(Control);
        lcdNumber_3->setObjectName("lcdNumber_3");
        lcdNumber_3->setGeometry(QRect(640, 115, 64, 23));
        lcdNumber_4 = new QLCDNumber(Control);
        lcdNumber_4->setObjectName("lcdNumber_4");
        lcdNumber_4->setGeometry(QRect(640, 200, 64, 23));
        lcdNumber_5 = new QLCDNumber(Control);
        lcdNumber_5->setObjectName("lcdNumber_5");
        lcdNumber_5->setGeometry(QRect(640, 250, 64, 23));
        lcdNumber_6 = new QLCDNumber(Control);
        lcdNumber_6->setObjectName("lcdNumber_6");
        lcdNumber_6->setGeometry(QRect(640, 156, 64, 23));
        label_7 = new QLabel(Control);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(20, 10, 111, 41));
        QFont font1;
        font1.setPointSize(20);
        label_7->setFont(font1);
        layoutWidget = new QWidget(Control);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(10, 60, 311, 41));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        radioButton = new QRadioButton(layoutWidget);
        radioButton->setObjectName("radioButton");
        radioButton->setEnabled(true);
        QFont font2;
        font2.setPointSize(12);
        radioButton->setFont(font2);

        horizontalLayout->addWidget(radioButton);

        radioButton_2 = new QRadioButton(layoutWidget);
        radioButton_2->setObjectName("radioButton_2");
        radioButton_2->setFont(font2);

        horizontalLayout->addWidget(radioButton_2);

        radioButton_3 = new QRadioButton(layoutWidget);
        radioButton_3->setObjectName("radioButton_3");
        radioButton_3->setFont(font2);

        horizontalLayout->addWidget(radioButton_3);

        label_8 = new QLabel(Control);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(100, 140, 240, 240));

        retranslateUi(Control);

        QMetaObject::connectSlotsByName(Control);
    } // setupUi

    void retranslateUi(QWidget *Control)
    {
        Control->setWindowTitle(QCoreApplication::translate("Control", "Form", nullptr));
        label->setText(QCoreApplication::translate("Control", "\345\244\264\351\203\250", nullptr));
        label_2->setText(QCoreApplication::translate("Control", "\345\267\246\350\207\202\345\261\225\345\274\200", nullptr));
        label_3->setText(QCoreApplication::translate("Control", "\345\267\246\350\207\202\346\227\213\350\275\254", nullptr));
        label_4->setText(QCoreApplication::translate("Control", "\345\217\263\350\207\202\345\261\225\345\274\200", nullptr));
        label_5->setText(QCoreApplication::translate("Control", "\345\217\263\350\207\202\346\227\213\350\275\254", nullptr));
        label_6->setText(QCoreApplication::translate("Control", "\345\272\225\347\233\230", nullptr));
        label_7->setText(QCoreApplication::translate("Control", "\351\200\211\346\213\251\346\250\241\345\274\217", nullptr));
        radioButton->setText(QCoreApplication::translate("Control", "\351\222\237\350\241\250\346\250\241\345\274\217", nullptr));
        radioButton_2->setText(QCoreApplication::translate("Control", "\346\216\247\345\210\266\346\250\241\345\274\217", nullptr));
        radioButton_3->setText(QCoreApplication::translate("Control", "\345\275\225\345\210\266\346\250\241\345\274\217", nullptr));
        label_8->setText(QCoreApplication::translate("Control", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Control: public Ui_Control {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTROL_H
