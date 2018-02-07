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

QJsonParseError::ParseError OpenWeather::parseReply(QNetworkReply &reply, OpenWeather::Weather &weather)
{
    QJsonParseError jsonErr;
    QJsonDocument json = QJsonDocument::fromJson(reply.readAll(), &jsonErr);
    if (json.isNull()) {
        qWarning() << "Json validation failed" << jsonErr.errorString();
        return jsonErr.error;
    }

    qDebug() << "Validation of response done:" << jsonErr.errorString();

    QJsonObject jObj = json.object();
    if (jObj.contains("coord") && jObj["coord"].isObject()) {
      qDebug() << "Coord found";

      weather.coord.isValid = true;
      QJsonObject jCoordObj = jObj["coord"].toObject();

      if (jCoordObj.contains("lon") && jCoordObj["lon"].isDouble())
          weather.coord.lon = jCoordObj["lon"].toDouble();

      if (jCoordObj.contains("lan") && jCoordObj["lan"].isDouble())
          weather.coord.lat = jCoordObj["lat"].toDouble();
    } else {
        weather.coord.isValid = false;
    }

    if (jObj.contains("weather") && jObj["weather"].isArray()) {
        qDebug() << "Weather found";

        weather.weather.isValid = true;
        QJsonArray jWeatherArray = jObj["weather"].toArray();
        if (!jWeatherArray.isEmpty()) {
          for (int i = 0; i < jWeatherArray.size(); i++) {

            QJsonObject jWeatherObj = jWeatherArray.at(i).toObject();

            if (jWeatherObj.contains("id") && jWeatherObj["id"].isDouble())
                weather.weather.id = jWeatherObj["id"].toInt();

            if (jWeatherObj.contains("main") && jWeatherObj["main"].isString())
                weather.weather.main = jWeatherObj["main"].toString();

            if (jWeatherObj.contains("description") && jWeatherObj["description"].isString())
                weather.weather.description = jWeatherObj["description"].toString();

            if (jWeatherObj.contains("icon") && jWeatherObj["icon"].isString())
                weather.weather.icon = jWeatherObj["icon"].toString();
          }
        }
    } else {
        weather.weather.isValid = false;
    }

    if (jObj.contains("main") && jObj["main"].isObject()) {
        qDebug() << "Main found";

        weather.main.isValid = true;
        QJsonObject jMainObj = jObj["main"].toObject();

        //Get temperature
        if (jMainObj.contains("temp") && jMainObj["temp"].isDouble())
          weather.main.temperature = jMainObj["temp"].toDouble();

        //Get pressure
        if (jMainObj.contains("pressure") && jMainObj["pressure"].isDouble())
          weather.main.pressure = jMainObj["pressure"].toDouble();

        // Get humidity
        if (jMainObj.contains("humidity") && jMainObj["humidity"].toDouble())
          weather.main.himidity = jMainObj["humidity"].toDouble();
    } else {
        weather.main.isValid = false;
    }

    if (jObj.contains("wind") && jObj["wind"].isObject()) {
        qDebug() << "Wind found";

        weather.wind.isValid = true;
        QJsonObject jWindObj = jObj["wind"].toObject();

        if (jWindObj.contains("speed") && jWindObj["speed"].isDouble())
            weather.wind.speed = jWindObj["speed"].toDouble();

        if (jWindObj.contains("deg") && jWindObj["deg"].isDouble())
            weather.wind.deg = jWindObj["deg"].toDouble();
    } else {
        weather.wind.isValid = false;
    }

    if (jObj.contains("clouds") && jObj["clouds"].isObject()) {
        qDebug() << "Clouds found";

        weather.clouds.isValid = true;
        QJsonObject jCloudsObj = jObj["clouds"].toObject();

        if (jCloudsObj.contains("all") && jCloudsObj["all"].isDouble())
            weather.clouds.all = jCloudsObj["all"].toDouble();
    } else {
        weather.clouds.isValid = false;
    }

    if (jObj.contains("rain") && jObj["rain"].isObject()) {
        qDebug() << "Rain found";

        weather.rain.isValid = true;
        QJsonObject jRainObj = jObj["rain"].toObject();

        if (jRainObj.contains("3h") && jRainObj["3h"].isDouble())
            weather.rain.h3 = jRainObj["3h"].toDouble();
    } else {
        weather.rain.isValid = false;
    }

    if (jObj.contains("snow") && jObj["snow"].isObject()) {
        qDebug() << "snow found";

        weather.snow.isValid = true;
        QJsonObject jSnowObj = jObj["snow"].toObject();

        if (jSnowObj.contains("3h") && jSnowObj["3h"].isDouble())
            weather.snow.h3 = jSnowObj["3h"].toDouble();
    } else {
        weather.snow.isValid = false;
    }

    if (jObj.contains("sys") && jObj["sys"].isObject()) {
        qDebug() << "Sys found";

        weather.sys.isValid = true;
        QJsonObject jSysObj = jObj["sys"].toObject();

        if (jSysObj.contains("type") && jSysObj["type"].isDouble())
            weather.sys.type = jSysObj["type"].toDouble();

        if (jSysObj.contains("id") && jSysObj["id"].isDouble())
            weather.sys.id = jSysObj["id"].toDouble();

        if (jSysObj.contains("message") && jSysObj["message"].isDouble())
            weather.sys.message = jSysObj["message"].toDouble();

        if (jSysObj.contains("country") && jSysObj["country"].isString())
            weather.sys.country = jSysObj["country"].toString();

        if (jSysObj.contains("sunrise") && jSysObj["sunrise"].isDouble())
            weather.sys.sunrise = jSysObj["sunrise"].toDouble();

        if (jSysObj.contains("sunset") && jSysObj["sunset"].isDouble())
            weather.sys.sunset = jSysObj["sunset"].toDouble();
    } else {
        weather.sys.isValid = false;
    }

    if (jObj.contains("visibility") && jObj["visibility"].isDouble()) {
        qDebug() << "Visibility found";
        weather.visibility = jObj["visibility"].toDouble();
    }

    if (jObj.contains("id") && jObj["id"].isDouble()) {
        qDebug() << "Id found";
        weather.id = jObj["id"].toInt();
    }

    if (jObj.contains("name") && jObj["name"].isString()) {
        qDebug() << "Name found";
        weather.name = jObj["name"].toString();
    }

    weather.isValid = true;

    return QJsonParseError::ParseError::NoError;
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

    connect(reply, &QNetworkReply::finished, this, &OpenWeather::onResponseSend);
}

void OpenWeather::onResponseSend()
{
    qDebug() << "Reqest finished got reply" << reply->errorString();
    if (reply->error()) {
        delete reply;
        emit error();
        return;
    }

    Weather weather;
    if (QJsonParseError::ParseError::NoError == parseReply(*reply, weather)) {
        qDebug() << weather;
        emit finished(weather);
    } else {
        emit error();
    }

    delete reply;
}

QDebug operator<<(QDebug stream, OpenWeather::Weather &weather)
{
    if (weather.isValid == false) {
        stream << "data invalid";
        return stream;
    }

    stream << "Weather for:" << weather.name << "id:" << weather.id << endl;

    if (weather.weather.isValid) {
        stream << "Main:" << weather.weather.main <<
                  "Icon:" << weather.weather.icon << endl;
        stream << "Description:" << weather.weather.description << endl;
    }

    if (weather.main.isValid)
        stream << "Temperature:" << weather.main.temperature <<
                  "Pressure:"    << weather.main.pressure    <<
                  "Humidity:"    << weather.main.himidity    << endl;

    if (weather.wind.isValid)
        stream << "Wind speed" << weather.wind.speed <<
                  "Direction:" << weather.wind.deg   << endl;

    if (weather.clouds.isValid)
        stream << "Cloudiness: " << weather.clouds.all << "%" << endl;

    if (weather.rain.isValid)
        stream << "Rain volume for last 3h:" << weather.rain.h3 << endl;

    if (weather.snow.isValid)
        stream << "Snow volume for last 3h:" << weather.snow.h3 << endl;

    if (weather.sys.isValid) {
        QDateTime qdt;
        QTime sunrise;
        QTime sunset;

        qdt.setSecsSinceEpoch(weather.sys.sunrise);
        sunrise = qdt.time();

        qdt.setSecsSinceEpoch(weather.sys.sunset);
        sunset = qdt.time();
        stream << "Sunrise:" << sunrise.toString("hh:mm:ss") << endl;
        stream << "Sunset:" << sunset.toString("hh:mm:ss") << endl;
        stream << "Country:" << weather.sys.country << endl;
    }

    return stream;
}
