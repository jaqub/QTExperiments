#include <QCoreApplication>
#include <QUrl>
#include <QUrlQuery>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QUrlQuery urlQuery;
    urlQuery.addQueryItem("appid", "");
    urlQuery.addQueryItem("id", "2172797");

    QUrl openWeather;
    openWeather.setScheme("http");
    openWeather.setHost("api.openweathermap.org");
    openWeather.setPath("/data/2.5/weather");
    openWeather.setQuery(urlQuery);

    qDebug() << "Will send request to OpenWeater: " << openWeather.toString();

    QNetworkAccessManager *netMgr = new QNetworkAccessManager();
    QNetworkReply *response = netMgr->get(QNetworkRequest(openWeather));
    while (response->isRunning()) {
      if (response->error())
          break;
      qDebug() << "Waiting response";
      sleep(1);
    }

    qDebug() << "Request has finished" << response->readLine(500);

    return a.exec();
}
