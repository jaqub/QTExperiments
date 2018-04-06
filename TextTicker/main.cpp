#include "TextTicker.h"
#include <QApplication>
#include <QStringLiteral>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TextTicker w;
    w.setText(QStringLiteral("Hunter - Śmierci Śmiech"));
    w.show();
    w.setInterval(10);
    return a.exec();
}
