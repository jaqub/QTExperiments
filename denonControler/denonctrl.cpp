#include "denonctrl.h"
#include <QtNetwork/QTcpSocket>
#include <QFile>
#include <QDebug>
#include <QSocketNotifier>
#include <unistd.h>

DenonCtrl::DenonCtrl()
{
    mSock = new QTcpSocket(this);
    Q_CHECK_PTR(mSock);

    mStdInNotifier = new QSocketNotifier(STDIN_FILENO, QSocketNotifier::Read, this);

    connect(mSock, &QTcpSocket::connected, this ,&DenonCtrl::connected);
    connect(mSock, &QTcpSocket::disconnected, this, &DenonCtrl::disconnected);
    connect(mSock, &QTcpSocket::readyRead, this, &DenonCtrl::readFromSock);
    mSock->connectToHost("192.168.1.106", 23);

    connect(mStdInNotifier, &QSocketNotifier::activated, this, &DenonCtrl::readFromStdIn);
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

qint64 DenonCtrl::readFromSock()
{
    qint64 nBytes = mSock->bytesAvailable();
    char *buff = new char[nBytes + 1];

    qint64 nRead = mSock->read(buff, nBytes);
    buff[nRead] = '\0';
    qInfo() << "(DENON):" << nBytes << "B -" << buff;

    delete [] buff;

    return nRead;
}

qint64 DenonCtrl::readFromStdIn()
{
    char buff[256];
    int nBytes = read(STDIN_FILENO, buff, 256);
    buff[nBytes - 1] = 0x0D;
    mSock->write(buff, nBytes);
    qDebug() << "(STDIN):" << buff;
    return nBytes;
}
