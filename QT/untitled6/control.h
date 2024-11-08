#ifndef CONTROL_H
#define CONTROL_H

#include <QWidget>

namespace Ui {
class Control;
}

class Control : public QWidget
{
    Q_OBJECT

public:
    explicit Control(QWidget *parent = nullptr);
    ~Control();

private slots:
    void on_horizontalSlider_2_valueChanged(int value);

private:
    Ui::Control *ui;
};

#endif // CONTROL_H
