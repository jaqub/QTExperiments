#ifndef OPENWEATHER_H
#define OPENWEATHER_H

#include <QObject>
#include <QVector>
#include <QtNetwork>

class OpenWeather : public QObject
{
    Q_OBJECT
public:
    typedef enum {
        Standard = 0,
        Metric   = 1,
        Imperial = 2,
    } UnitFormat;

    class Weather
    {
    public:
        struct weather_t {
            int id;
            QString main;
            QString description;
            QString icon;
        };

        struct {
            double lon;
            double lat;
            bool isValid;
        } coord;

        struct {
            double_t temperature;
            double_t pressure;
            double_t himidity;
            bool isValid;
        } main;

        struct {
            double_t speed;
            double_t deg;
            bool isValid;
        } wind;

        struct {
            double_t all;
            bool isValid;
        } clouds;

        struct {
            double_t h3;
            bool isValid;
        } rain;

        struct {
            double_t h3;
            bool isValid;
        } snow;

        struct {
            double_t type;
            double_t id;
            double_t message;
            QString country;
            double_t sunrise;
            double_t sunset;
            bool isValid;
        } sys;

        QVector<weather_t> weather;
        double_t visibility;
        int id;
        QString name;
        bool isValid;
    };

    explicit OpenWeather(QObject *parent = nullptr, const QString &appid = "");
    ~OpenWeather();

    void get(const QString &id);
    void setAppid(const QString &appid) { OpenWeather::appid = appid; }
    void setUnitFormat(OpenWeather::UnitFormat unit = Standard) { OpenWeather::format = unit; }
    OpenWeather::UnitFormat getUnitFormat(void) { return format; }

signals:
      void finished(OpenWeather::Weather weather);
      void error(void);

public slots:

      void onResponseSend();

private:
    QJsonParseError::ParseError parseReply(QNetworkReply &reply, OpenWeather::Weather &weather);

    QUrl *url;
    QNetworkAccessManager *qnam;
    QNetworkReply *reply;

    QString appid;
    QString id;
    UnitFormat format;
};

QDebug operator<<(QDebug stream, OpenWeather::Weather &weather);

#endif // OPENWEATHER_H
