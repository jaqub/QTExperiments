#include "denonctrl.h"
#include <QtNetwork/QTcpSocket>
#include <QDebug>

DenonCtrl::DenonCtrl() : mSock(new QTcpSocket(this))
{
    Q_CHECK_PTR(mSock);

    connect(mSock, &QTcpSocket::connected, this ,&DenonCtrl::connected);
    connect(mSock, &QTcpSocket::disconnected, this, &DenonCtrl::disconnected);
    connect(mSock, &QTcpSocket::readyRead, this, &DenonCtrl::readyRead);

    mSock->connectToHost("192.168.1.106", 23);
}

DenonCtrl::~DenonCtrl()
{
    mSock->disconnectFromHost();
}

void DenonCtrl::connected()
{
    qInfo() << "Connected to server";
}

void DenonCtrl::disconnected()
{
    qInfo() << "Disconnected";
}

void DenonCtrl::readyRead()
{
   qInfo() << "Got data:" << mSock->bytesAvailable() << "B";
}
