#ifndef DENONCTRL_H
#define DENONCTRL_H

#include <QObject>

class QTcpSocket;

class DenonCtrl : public QObject
{
    Q_OBJECT

public:
    DenonCtrl();
    virtual ~DenonCtrl();

protected slots:
    void connected();
    void disconnected();
    void readyRead();

private:
    QTcpSocket *mSock;
};

#endif // DENONCTRL_H
