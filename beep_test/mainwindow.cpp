#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QTime>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , cnt(30)
{
    ui->setupUi(this);
    ui->label->setText(QString::number(cnt));

    timer = new QTimer();
    connect(ui->enable, SIGNAL(clicked(bool)), this, SLOT(enableTimer(bool)));
    connect(ui->reset, SIGNAL(clicked(bool)), this, SLOT(resetTimer(void)));
    connect(timer, SIGNAL(timeout(void)), this, SLOT(timeout(void)));
    timer->setInterval(1000);

    qDebug() << "Timer created";
}

MainWindow::~MainWindow()
{
    timer->stop();
    delete timer;
    delete ui;
}

void MainWindow::enableTimer(bool enable)
{
    if (enable)
        timer->start();
    else
        timer->stop();

    qDebug() << "Timer: " << (enable ? " enabled" : " disabled");
}

void MainWindow::resetTimer(void)
{
    qDebug() << "Timer reset";
    timer->start();
    cnt = 30;
    ui->label->setText(QString::number(cnt));
}

void MainWindow::timeout()
{
    cnt--;
    if (cnt == 0) {
        qDebug() << "Timer timeout";
        QApplication::beep();
        cnt = 30;
    }

    ui->label->setText(QString::number(cnt));
}
