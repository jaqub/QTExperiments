#ifndef QWEATHER_H
#define QWEATHER_H

#include <QWidget>
#include <QSize>

class QPaintEvent;
class QPainter;

class QWeather : public QWidget
{
    Q_OBJECT

public:

    class WeatherItem {

    public:
        WeatherItem(double in) : temperature(in) {}

        double temp() const { return temperature; }

    private:
        double temperature;
    };

    QWeather(QWidget *parent = 0);

    ~QWeather();

    QSize minimumSizeHint() const;

    QSize sizeHint() const;

    void append(WeatherItem *item);

    void clear();

protected:
    void paintEvent(QPaintEvent *event);

private:
    QVector< WeatherItem* > mForecast;

    static const int margin = 25;

    double minY;

    double maxY;

    int numYTicks;

    void drawYGrid(QPainter *painter);

    void drawCurve(QPainter *painter);

    double adjustAxis(double &min, double &max, int &numTicks);

};

//const int QWeather::margin = 15;

#endif // QWEATHER_H
