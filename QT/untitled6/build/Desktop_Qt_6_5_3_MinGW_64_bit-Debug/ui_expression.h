/********************************************************************************
** Form generated from reading UI file 'expression.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXPRESSION_H
#define UI_EXPRESSION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Expression
{
public:
    QPushButton *pushButton_anger;
    QPushButton *pushButton_disdain;
    QPushButton *pushButton_excited;
    QPushButton *pushButton_fear;
    QPushButton *pushButton_left;
    QPushButton *pushButton_normal;
    QPushButton *pushButton_right;
    QPushButton *pushButton_sad;
    QPushButton *pushButton_anger_9;
    QPushButton *pushButton_anger_10;
    QPushButton *pushButton_anger_11;
    QPushButton *Button_start;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;

    void setupUi(QWidget *Expression)
    {
        if (Expression->objectName().isEmpty())
            Expression->setObjectName("Expression");
        Expression->resize(780, 650);
        pushButton_anger = new QPushButton(Expression);
        pushButton_anger->setObjectName("pushButton_anger");
        pushButton_anger->setGeometry(QRect(60, 50, 120, 120));
        pushButton_anger->setStyleSheet(QString::fromUtf8("image: url(:/expression/build/Desktop_Qt_6_5_3_MinGW_64_bit-Debug/anger.png);"));
        pushButton_disdain = new QPushButton(Expression);
        pushButton_disdain->setObjectName("pushButton_disdain");
        pushButton_disdain->setGeometry(QRect(240, 50, 120, 120));
        pushButton_disdain->setStyleSheet(QString::fromUtf8("image: url(:/expression/build/Desktop_Qt_6_5_3_MinGW_64_bit-Debug/disdain.png);"));
        pushButton_excited = new QPushButton(Expression);
        pushButton_excited->setObjectName("pushButton_excited");
        pushButton_excited->setGeometry(QRect(430, 50, 120, 120));
        pushButton_excited->setStyleSheet(QString::fromUtf8("image: url(:/expression/build/Desktop_Qt_6_5_3_MinGW_64_bit-Debug/excited.png);"));
        pushButton_fear = new QPushButton(Expression);
        pushButton_fear->setObjectName("pushButton_fear");
        pushButton_fear->setGeometry(QRect(620, 50, 120, 120));
        pushButton_fear->setStyleSheet(QString::fromUtf8("image: url(:/expression/build/Desktop_Qt_6_5_3_MinGW_64_bit-Debug/fear.png);"));
        pushButton_left = new QPushButton(Expression);
        pushButton_left->setObjectName("pushButton_left");
        pushButton_left->setGeometry(QRect(60, 250, 120, 120));
        pushButton_left->setStyleSheet(QString::fromUtf8("image: url(:/expression/build/Desktop_Qt_6_5_3_MinGW_64_bit-Debug/left.png);"));
        pushButton_normal = new QPushButton(Expression);
        pushButton_normal->setObjectName("pushButton_normal");
        pushButton_normal->setGeometry(QRect(240, 250, 120, 120));
        pushButton_normal->setStyleSheet(QString::fromUtf8("image: url(:/expression/build/Desktop_Qt_6_5_3_MinGW_64_bit-Debug/normal.png);"));
        pushButton_right = new QPushButton(Expression);
        pushButton_right->setObjectName("pushButton_right");
        pushButton_right->setGeometry(QRect(430, 250, 120, 120));
        pushButton_right->setStyleSheet(QString::fromUtf8("image: url(:/expression/build/Desktop_Qt_6_5_3_MinGW_64_bit-Debug/right.png);"));
        pushButton_sad = new QPushButton(Expression);
        pushButton_sad->setObjectName("pushButton_sad");
        pushButton_sad->setGeometry(QRect(620, 250, 120, 120));
        pushButton_sad->setStyleSheet(QString::fromUtf8("image: url(:/expression/build/Desktop_Qt_6_5_3_MinGW_64_bit-Debug/sad.png);"));
        pushButton_anger_9 = new QPushButton(Expression);
        pushButton_anger_9->setObjectName("pushButton_anger_9");
        pushButton_anger_9->setGeometry(QRect(60, 450, 120, 120));
        pushButton_anger_9->setStyleSheet(QString::fromUtf8("image: url(:/expression/build/Desktop_Qt_6_5_3_MinGW_64_bit-Debug/anger.png);"));
        pushButton_anger_10 = new QPushButton(Expression);
        pushButton_anger_10->setObjectName("pushButton_anger_10");
        pushButton_anger_10->setGeometry(QRect(240, 450, 120, 120));
        pushButton_anger_10->setStyleSheet(QString::fromUtf8("image: url(:/expression/build/Desktop_Qt_6_5_3_MinGW_64_bit-Debug/anger.png);"));
        pushButton_anger_11 = new QPushButton(Expression);
        pushButton_anger_11->setObjectName("pushButton_anger_11");
        pushButton_anger_11->setGeometry(QRect(430, 450, 120, 120));
        pushButton_anger_11->setStyleSheet(QString::fromUtf8("image: url(:/expression/build/Desktop_Qt_6_5_3_MinGW_64_bit-Debug/anger.png);"));
        Button_start = new QPushButton(Expression);
        Button_start->setObjectName("Button_start");
        Button_start->setGeometry(QRect(640, 470, 111, 111));
        QFont font;
        font.setPointSize(18);
        Button_start->setFont(font);
        label = new QLabel(Expression);
        label->setObjectName("label");
        label->setGeometry(QRect(60, 170, 120, 50));
        QFont font1;
        font1.setPointSize(16);
        label->setFont(font1);
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(Expression);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(240, 170, 120, 50));
        label_2->setFont(font1);
        label_2->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(Expression);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(430, 170, 120, 50));
        label_3->setFont(font1);
        label_3->setAlignment(Qt::AlignCenter);
        label_4 = new QLabel(Expression);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(620, 170, 120, 50));
        label_4->setFont(font1);
        label_4->setAlignment(Qt::AlignCenter);
        label_5 = new QLabel(Expression);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(620, 370, 120, 50));
        label_5->setFont(font1);
        label_5->setAlignment(Qt::AlignCenter);
        label_6 = new QLabel(Expression);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(430, 370, 120, 50));
        label_6->setFont(font1);
        label_6->setAlignment(Qt::AlignCenter);
        label_7 = new QLabel(Expression);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(240, 370, 120, 50));
        label_7->setFont(font1);
        label_7->setAlignment(Qt::AlignCenter);
        label_8 = new QLabel(Expression);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(60, 370, 120, 50));
        label_8->setFont(font1);
        label_8->setAlignment(Qt::AlignCenter);

        retranslateUi(Expression);

        QMetaObject::connectSlotsByName(Expression);
    } // setupUi

    void retranslateUi(QWidget *Expression)
    {
        Expression->setWindowTitle(QCoreApplication::translate("Expression", "Form", nullptr));
        pushButton_anger->setText(QString());
        pushButton_disdain->setText(QString());
        pushButton_excited->setText(QString());
        pushButton_fear->setText(QString());
        pushButton_left->setText(QString());
        pushButton_normal->setText(QString());
        pushButton_right->setText(QString());
        pushButton_sad->setText(QString());
        pushButton_anger_9->setText(QString());
        pushButton_anger_10->setText(QString());
        pushButton_anger_11->setText(QString());
        Button_start->setText(QCoreApplication::translate("Expression", "\346\222\255\346\224\276", nullptr));
        label->setText(QCoreApplication::translate("Expression", "\346\204\244\346\200\222", nullptr));
        label_2->setText(QCoreApplication::translate("Expression", "\344\270\215\345\261\221", nullptr));
        label_3->setText(QCoreApplication::translate("Expression", "\345\205\264\345\245\213", nullptr));
        label_4->setText(QCoreApplication::translate("Expression", "\346\203\212\346\201\220", nullptr));
        label_5->setText(QCoreApplication::translate("Expression", "\351\232\276\350\277\207", nullptr));
        label_6->setText(QCoreApplication::translate("Expression", "\345\217\263\350\275\254", nullptr));
        label_7->setText(QCoreApplication::translate("Expression", "\351\235\231\346\200\201", nullptr));
        label_8->setText(QCoreApplication::translate("Expression", "\345\267\246\350\275\254", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Expression: public Ui_Expression {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXPRESSION_H
