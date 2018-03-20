#include "denonctrl.h"
#include "ui_denonctrl.h"

DenonCtrl::DenonCtrl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DenonCtrl)
{
    ui->setupUi(this);
}

DenonCtrl::~DenonCtrl()
{
    delete ui;
}
