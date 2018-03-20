#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QTcpSocket;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void connected();

    void dataReceived();

    void setVolume(int aVolume);

private:

    Ui::Widget *ui;

    QTcpSocket *mSock;
};

#endif // WIDGET_H
