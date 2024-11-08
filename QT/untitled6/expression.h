#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <QWidget>
#include <QPushButton>
#include "tdicethread.h"

namespace Ui {
class Expression;
}

class Expression : public QWidget
{
    Q_OBJECT

public:
    explicit Expression(QWidget *parent = nullptr);
    ~Expression();

private slots:
    void on_pushButton_anger_clicked();

    void on_pushButton_disdain_clicked();

    void on_pushButton_excited_clicked();

    void on_pushButton_fear_clicked();

    void on_pushButton_left_clicked();

    void on_pushButton_normal_clicked();

    void on_pushButton_right_clicked();

    void on_pushButton_sad_clicked();
    void resetAllButtons();
    void setButtonSelected(QPushButton *button);

    void on_Button_start_clicked();

private:
    Ui::Expression *ui;
    TDiceTHread *thread_Send;
    bool m_isChecked;        // 用于跟踪按钮的状态
    QPushButton *currentlySelectedButton = nullptr; // 用于跟踪当前选中的按钮
    QString getBaseStyle(const QString &imagePath) const;
};

#endif // EXPRESSION_H
