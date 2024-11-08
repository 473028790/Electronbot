#include "vision.h"
#include "ui_vision.h"

Vision::Vision(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Vision)
{
    ui->setupUi(this);
}

Vision::~Vision()
{
    delete ui;
}
