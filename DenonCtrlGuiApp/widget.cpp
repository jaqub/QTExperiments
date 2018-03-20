#include "widget.h"
#include "ui_widget.h"
#include <QTcpSocket>

Widget::Widget(QWidget *parent) :
    QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->volume->setMinimum(0);
    mSock = new QTcpSocket(this);
    Q_CHECK_PTR(mSock);

    connect(mSock, &QTcpSocket::connected, this, &Widget::connected);
    connect(mSock, &QTcpSocket::readyRead, this, &Widget::dataReceived);
    mSock->connectToHost("192.168.1.103", 23);

    connect(ui->volume, &QDial::valueChanged, this, &Widget::setVolume);
}

Widget::~Widget()
{
    delete ui;
    if (mSock && mSock->state() == QTcpSocket::ConnectedState)
        mSock->disconnect();
}

void Widget::connected()
{
    qDebug() << "Connected to Denon";
    mSock->write("PW?\r");
}

void Widget::dataReceived()
{
    QByteArray data = mSock->readAll();

    qDebug() << "(DENON):" << data;

    if (data.startsWith("PWON")) {
        ui->volume->setEnabled(true);
        mSock->write("MV?\r");
    } else if (data.startsWith("PWSTANDBY")) {
        ui->volume->setValue(0);
        ui->volume->setEnabled(false);
    }else if (data.startsWith("MVMAX")) {
        ui->volume->setMaximum(data.mid(6,2).toInt());
    } else if (data.startsWith("MV")) {
        int volume = data.mid(2,2).toInt();
        if (ui->volume->value() != volume)
            ui->volume->setValue(volume);
    }
}

void Widget::setVolume(int aVolume)
{
    QString volume("MV%1\r");
    qDebug() << volume.arg(aVolume).toLatin1();
    mSock->write(volume.arg(aVolume).toLatin1());
}
