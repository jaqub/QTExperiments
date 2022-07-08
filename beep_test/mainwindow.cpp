#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QTime>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , cnt(180)
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
    enableTimer(false);
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
    cnt = 180;
    ui->label->setText(QString::number(cnt));
}

void MainWindow::timeout()
{
    cnt--;

    // Make beep every 30 sec
    if (!(cnt % 30))
        QApplication::beep();

    // Additionally make one more beep 1 sec before timeout
    if (cnt == 1)
        QApplication::beep();

    if (cnt == 0) {
        qDebug() << "Timer timeout";
        cnt = 180;
    }

    ui->label->setText(QString::number(cnt));
}
