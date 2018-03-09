#include <QCoreApplication>
#include "denonctrl.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    DenonCtrl *denon = new DenonCtrl();

    return a.exec();
}
