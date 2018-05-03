#include "qweather.h"

#include <QDebug>
#include <QPainter>
#include <QRect>

QWeather::QWeather(QWidget *parent)
    : QWidget(parent), minY(0), maxY(10), numYTicks(1)
{
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
    if (mForecast.isEmpty()) {
        minY = item->temp();
        maxY = minY + 1;
    } else if (item->temp() > maxY) {
        maxY = item->temp();
    } else if (item->temp() < minY) {
        minY = item->temp();
    }

    mForecast.append(item);

    adjustAxis(minY, maxY, numYTicks);
    update();
}

void QWeather::clear()
{
  qDeleteAll(mForecast);
  mForecast.clear();
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

void QWeather::drawCurve(QPainter *painter)
{
    Q_ASSERT(painter != nullptr);

    QRect rect(margin, margin,
               width() - 2 * margin, height() - 2 * margin);

    int numXTicks = mForecast.size();
    int xStep = rect.width() / numXTicks;
    double dy = rect.height() / (maxY - minY);
    QPolygon polyline(numXTicks);

    for (int i = 0; i < numXTicks; i++) {
        int x  = rect.left() + i * xStep;
        int y = rect.bottom() - (mForecast.at(i)->temp() - minY) * dy;
        polyline[i] = QPoint(x, y);
    }

    painter->drawPolyline(polyline);
}

void QWeather::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    drawYGrid(&painter);
    drawCurve(&painter);
}

double QWeather::adjustAxis(double &min, double &max, int &numTicks)
{
    const int MinTicks = 2;
    double grossStep = (max - min) / MinTicks;
    double step = std::pow(10.0, std::floor(std::log10(grossStep)));

    if (step * 5 < grossStep) {
      step *= 5;
    } else if (step * 2 < grossStep) {
        step *= 2;
    }

    numTicks = int(std::ceil(max / step) - std::floor(min / step));
    if (numTicks < MinTicks)
        numTicks = MinTicks;
    min = std::floor(min / step) * step;
    max = std::ceil(max / step) * step;

    return step;
}

