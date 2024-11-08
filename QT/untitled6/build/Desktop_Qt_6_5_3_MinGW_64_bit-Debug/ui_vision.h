/********************************************************************************
** Form generated from reading UI file 'vision.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VISION_H
#define UI_VISION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Vision
{
public:
    QPushButton *pushButton;

    void setupUi(QWidget *Vision)
    {
        if (Vision->objectName().isEmpty())
            Vision->setObjectName("Vision");
        Vision->resize(780, 650);
        pushButton = new QPushButton(Vision);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(530, 490, 80, 24));

        retranslateUi(Vision);

        QMetaObject::connectSlotsByName(Vision);
    } // setupUi

    void retranslateUi(QWidget *Vision)
    {
        Vision->setWindowTitle(QCoreApplication::translate("Vision", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("Vision", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Vision: public Ui_Vision {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VISION_H
