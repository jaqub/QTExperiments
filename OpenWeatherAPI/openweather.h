#ifndef OPENWEATHER_H
#define OPENWEATHER_H

#include <QObject>
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
        struct {
            double lon;
            double lat;
        } coord;

        struct {
            int id;
            QString main;
            QString description;
            QString icon;
        } weather;

        struct {
            double_t temperature;
            double_t pressure;
            double_t himidity;
        } main;

        struct {
            double_t speed;
            double_t deg;
        } wind;

        struct {
            double_t all;
        } clouds;

        struct {
            double_t h3;
        } rain;

        struct {
            double_t h3;
        } snow;

        struct {
            double_t type;
            double_t id;
            double_t message;
            QString country;
            double_t sunrise;
            double_t sunset;
        } sys;

        double_t visibility;
        int id;
        QString name;
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

#endif // OPENWEATHER_H
