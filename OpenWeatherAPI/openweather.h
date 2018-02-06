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

    explicit OpenWeather(QObject *parent = nullptr, const QString &appid = "");
    ~OpenWeather();

    void get(const QString &id);
    void setAppid(const QString &appid) { OpenWeather::appid = appid; }
    void setUnitFormat(OpenWeather::UnitFormat unit = Standard) { OpenWeather::format = unit; }
    OpenWeather::UnitFormat getUnitFormat(void) { return format; }

signals:

public slots:

      void finished();

private:
    QUrl *url;
    QNetworkAccessManager *qnam;
    QNetworkReply *reply;

    QString appid;
    QString id;
    UnitFormat format;
};

#endif // OPENWEATHER_H
