#include "cwtest.h"
#include "ui_cwtest.h"

CWTest::CWTest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CWTest)
{
    ui->setupUi(this);
}

CWTest::~CWTest()
{
    delete ui;
}
