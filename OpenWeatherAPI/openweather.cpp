#include "openweather.h"

OpenWeather::OpenWeather(QObject *parent, const QString &appid) :
    QObject(parent),
    url(new QUrl()),
    appid(appid)
{
  qnam = new QNetworkAccessManager(this);

  url->setScheme("http");
  url->setHost("api.openweathermap.org");
  url->setPath("/data/2.5/weather");
}

OpenWeather::~OpenWeather()
{
    delete url;
}

void OpenWeather::get(const QString &id)
{
    QUrlQuery urlQuery;
    urlQuery.addQueryItem("appid", appid);
    urlQuery.addQueryItem("id", id);

    url->setQuery(urlQuery);

    qDebug() << "Will send request to: " << url->toString();

    reply = qnam->get(QNetworkRequest(*url));
    connect(reply, &QNetworkReply::finished, this, &OpenWeather::finished);
}

void OpenWeather::finished()
{
    qDebug() << "Reqest finished got reply" << reply->error();
    if (reply->error()) {
        delete reply;
        return;
    }

    qDebug() << reply->readAll();

    delete reply;
}
