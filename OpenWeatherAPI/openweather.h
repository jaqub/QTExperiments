#ifndef OPENWEATHER_H
#define OPENWEATHER_H

#include <QObject>
#include <QtNetwork>

class OpenWeather : public QObject
{
    Q_OBJECT
public:
    explicit OpenWeather(QObject *parent = nullptr, const QString &appid = "");
    ~OpenWeather();

    void get(const QString &id);
    void setAppid(const QString &appid) { OpenWeather::appid = appid; };

signals:

public slots:

      void finished();

private:
    QUrl *url;
    QNetworkAccessManager *qnam;
    QNetworkReply *reply;

    QString appid;
    QString id;
};

#endif // OPENWEATHER_H
