#include "TextTicker.h"

#include <QFontMetrics>
#include <QPainter>
#include <QPaintEvent>
#include <QTimerEvent>

TextTicker::TextTicker(QWidget *parent)
    : QWidget(parent), offset(0), timerId(0), timerInterval(30)
{
}

TextTicker::~TextTicker()
{

}

void TextTicker::setText(const QString &newText)
{
    myText = newText;
    update();
}

void TextTicker::setInterval(const int &interval)
{
    timerInterval = interval;
    if (timerId != 0)
        killTimer(timerId);

    if (timerInterval == -1)
        return;

    timerId = startTimer(timerInterval);
}

QSize TextTicker::sizeHint() const
{
    return fontMetrics().size(0, text());
}

void TextTicker::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    int textWidth = fontMetrics().width(text());
    if (textWidth < 1)
        return;

    painter.drawText(width() - offset, 0, textWidth, height(),
                     Qt::AlignLeft | Qt::AlignCenter, text());
}

void TextTicker::timerEvent(QTimerEvent *event)
{
    if (timerId != event->timerId())
        return QWidget::timerEvent(event);

    ++offset;
    if (offset >= width() + fontMetrics().width(text()))
        offset = 0;

    update();
}

void TextTicker::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);

    timerId = startTimer(timerInterval);
}

void TextTicker::hideEvent(QHideEvent *event)
{
    Q_UNUSED(event);

    killTimer(timerId);
    timerId = 0;
}
