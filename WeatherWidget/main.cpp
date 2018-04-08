#include "qweather.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWeather w;
    w.show();

    for (int i = 0; i < 10; i++)
      w.append(new QWeather::WeatherItem(qrand() % 40));

    return a.exec();
}
