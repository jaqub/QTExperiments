#include <QCoreApplication>
#include "openweather.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //OpenWeather *ow = new OpenWeather(Q_NULLPTR,  /* Enter API key here */  );
    ow->setUnitFormat(OpenWeather::UnitFormat::Metric);
    ow->get(QString("3081368"));

    return a.exec();
}
