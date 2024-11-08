/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action52;
    QAction *action2;
    QWidget *centralwidget;
    QWidget *widget;
    QPushButton *Button_control;
    QPushButton *Button_vision;
    QPushButton *Button_Attitude;
    QPushButton *Button_Watch;
    QPushButton *Button_Expression;
    QPushButton *Button_Teach;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1050, 736);
        action52 = new QAction(MainWindow);
        action52->setObjectName("action52");
        action2 = new QAction(MainWindow);
        action2->setObjectName("action2");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(230, 20, 780, 650));
        QFont font;
        font.setBold(false);
        widget->setFont(font);
        widget->setStyleSheet(QString::fromUtf8(""));
        Button_control = new QPushButton(centralwidget);
        Button_control->setObjectName("Button_control");
        Button_control->setGeometry(QRect(20, 20, 161, 41));
        Button_vision = new QPushButton(centralwidget);
        Button_vision->setObjectName("Button_vision");
        Button_vision->setGeometry(QRect(20, 80, 161, 41));
        Button_Attitude = new QPushButton(centralwidget);
        Button_Attitude->setObjectName("Button_Attitude");
        Button_Attitude->setGeometry(QRect(20, 140, 161, 41));
        Button_Watch = new QPushButton(centralwidget);
        Button_Watch->setObjectName("Button_Watch");
        Button_Watch->setGeometry(QRect(20, 200, 161, 41));
        Button_Expression = new QPushButton(centralwidget);
        Button_Expression->setObjectName("Button_Expression");
        Button_Expression->setGeometry(QRect(20, 260, 161, 41));
        Button_Teach = new QPushButton(centralwidget);
        Button_Teach->setObjectName("Button_Teach");
        Button_Teach->setGeometry(QRect(20, 320, 161, 41));
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        action52->setText(QCoreApplication::translate("MainWindow", "52", nullptr));
        action2->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        Button_control->setText(QCoreApplication::translate("MainWindow", "\347\224\265\345\255\220\350\204\221\345\243\263", nullptr));
        Button_vision->setText(QCoreApplication::translate("MainWindow", "\350\247\206\350\247\211\345\210\206\346\236\220", nullptr));
        Button_Attitude->setText(QCoreApplication::translate("MainWindow", "\345\247\277\346\200\201\350\257\206\345\210\253", nullptr));
        Button_Watch->setText(QCoreApplication::translate("MainWindow", "\350\247\202\345\275\261\346\250\241\345\274\217", nullptr));
        Button_Expression->setText(QCoreApplication::translate("MainWindow", "\350\241\250\346\203\205\345\212\250\344\275\234", nullptr));
        Button_Teach->setText(QCoreApplication::translate("MainWindow", "\347\244\272\346\225\231\346\250\241\345\274\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
