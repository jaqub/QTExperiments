#include <QCoreApplication>
#include "openweather.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    OpenWeather *ow = new OpenWeather(Q_NULLPTR, /* Enter API key here */ );
    ow->get(QString("2172797"));
    return a.exec();
}
