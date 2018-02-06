#include <QJsonDocument>
#include <QJsonObject>
#include "openweather.h"

OpenWeather::OpenWeather(QObject *parent, const QString &appid) :
    QObject(parent),
    url(new QUrl()),
    appid(appid),
    format(OpenWeather::UnitFormat::Standard)
{
  qnam = new QNetworkAccessManager(this);
  Q_CHECK_PTR(qnam);

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
    if (format == UnitFormat::Metric)
      urlQuery.addQueryItem("units", "metric");
    else if (format == UnitFormat::Imperial)
      urlQuery.addQueryItem("units", "imperial");

    url->setQuery(urlQuery);

    qDebug() << "Will send request to: " << url->toString();

    reply = qnam->get(QNetworkRequest(*url));
    Q_CHECK_PTR(reply);

    connect(reply, &QNetworkReply::finished, this, &OpenWeather::finished);
}

void OpenWeather::finished()
{
    qDebug() << "Reqest finished got reply" << reply->errorString();
    if (reply->error()) {
        delete reply;
        return;
    }

    QJsonParseError jsonErr;
    QJsonDocument json = QJsonDocument::fromJson(reply->readAll(), &jsonErr);
    if (json.isNull()) {
        qWarning() << "Json validation failed" << jsonErr.errorString();

        delete reply;
        return;
    }

    qDebug() << "Validation of response done:" << jsonErr.errorString();

    QJsonObject jObj;
    jObj = json.object();
    if (jObj.contains("main")) {
        qDebug() << "Main found";
        QJsonObject jMainObj = jObj["main"].toObject();

        //Get temperature
        if (jMainObj.contains("temp") && jMainObj["temp"].isDouble()) {
            qDebug() << "Temp: " << jMainObj["temp"].toDouble();
        }

        //Get pressure
        if (jMainObj.contains("pressure") && jMainObj["pressure"].isDouble()) {
            qDebug() << "Pressure: " << jMainObj["pressure"].toDouble();
        }

        // Get humidity
        if (jMainObj.contains("humidity") && jMainObj["humidity"].toDouble()) {
            qDebug() << "Humidity: " << jMainObj["humidity"].toDouble();
        }
    }

    delete reply;
}
