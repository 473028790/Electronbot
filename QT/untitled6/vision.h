#ifndef VISION_H
#define VISION_H

#include <QWidget>

namespace Ui {
class Vision;
}

class Vision : public QWidget
{
    Q_OBJECT

public:
    explicit Vision(QWidget *parent = nullptr);
    ~Vision();

private:
    Ui::Vision *ui;
};

#endif // VISION_H
