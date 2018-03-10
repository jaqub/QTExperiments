#ifndef DENONCTRL_H
#define DENONCTRL_H

#include <QObject>

class QTcpSocket;
class QFile;
class QSocketNotifier;

class DenonCtrl : public QObject
{
    Q_OBJECT

public:
    DenonCtrl();
    virtual ~DenonCtrl();

protected slots:
    void connected();
    void disconnected();
    qint64 readFromSock();
    qint64 readFromStdIn();

private:

    QTcpSocket *mSock;
    QSocketNotifier *mStdInNotifier;
};

#endif // DENONCTRL_H
