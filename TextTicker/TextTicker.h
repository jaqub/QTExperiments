#ifndef TEXTTICKER_H
#define TEXTTICKER_H

#include <QWidget>

class TextTicker : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(int interval READ interval WRITE setInterval NOTIFY intervalChanged)

public:
    TextTicker(QWidget *parent = 0);

    ~TextTicker();

    void setText(const QString &newText);

    QString text() const { return myText; }

    int interval() const { return timerInterval; }

    void setInterval(const int &interval);

    QSize sizeHint() const;

signals:
    void textChanged(const QString &newText);

    void intervalChanged(const int &newInterval);

protected:
    void paintEvent(QPaintEvent *event);

    void timerEvent(QTimerEvent *event);

    void showEvent(QShowEvent *event);

    void hideEvent(QHideEvent *event);


private:
    QString myText;

    int offset;

    int timerId;

    int timerInterval;
};

#endif // TEXTTICKER_H
