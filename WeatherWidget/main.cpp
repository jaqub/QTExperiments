#include "qweather.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWeather w;

    for (int i = 0; i < 40; i++)
      w.append(new QWeather::WeatherItem((qrand() % 20) - 20));

    w.show();
    return a.exec();
}
