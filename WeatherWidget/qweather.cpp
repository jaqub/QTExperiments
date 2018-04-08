#include "qweather.h"

#include <QDebug>
#include <QPainter>
#include <QRect>

QWeather::QWeather(QWidget *parent)
    : QWidget(parent), itemsShown(1), minY(-7), maxY(6), numYTicks(1)
{
    double step = adjustAxis(minY, maxY, numYTicks);
    qDebug() << "minY" << minY << "maxY" << maxY <<
                "ticks" << numYTicks << "step" << step;
}

QWeather::~QWeather()
{

}

QSize QWeather::minimumSizeHint() const
{
    return QSize(700, 130);
}

QSize QWeather::sizeHint() const
{
    return QSize(700, 130);
}

void QWeather::append(WeatherItem *item)
{
    forecast.append(item);
    itemsShown = forecast.size();
    if (itemsShown <= 0)
        itemsShown = 1;
    else if (itemsShown > 5)
        itemsShown = 5;

    update();
}
void QWeather::drawYGrid(QPainter *painter)
{
    Q_ASSERT(painter != nullptr);

    QRect rect(margin, margin,
               width() - 2 * margin, height() - 2 * margin);

    for (int i = 0; i < numYTicks + 1; i++) {
      int y = rect.bottom() - (i * rect.height() / numYTicks);

      double label = minY + (i * (maxY - minY) / numYTicks);
      painter->drawLine(rect.left(), y, rect.right(), y);
      painter->drawText(rect.left() - margin, y - 15, margin, 20,
                        Qt::AlignRight | Qt::AlignVCenter,
                        QString::number(label));
    }
}

void QWeather::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QRect rect(margin, 0, width(), height() - margin);
    if (!rect.isValid())
        return;

    QPainter painter(this);
    drawYGrid(&painter);
}

double QWeather::adjustAxis(double &min, double &max, int &numTicks)
{
    const int MinTicks = 2;
    double grossStep = (max - min) / MinTicks;
    double step = std::pow(10.0, std::floor(std::log10(grossStep)));

    if (step * 5 < grossStep) {
      step *= 5;
    } else if (step * 2 <= grossStep) {
        step *= 2;
    }

    numTicks = int(std::ceil(max / step) - std::floor(min / step));
    if (numTicks < MinTicks)
        numTicks = MinTicks;
    min = std::floor(min / step) * step;
    max = std::ceil(max / step) * step;

    return step;
}

