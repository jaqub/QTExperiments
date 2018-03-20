#ifndef DENONCTRL_H
#define DENONCTRL_H

#include <QWidget>

namespace Ui {
class DenonCtrl;
}

class DenonCtrl : public QWidget
{
    Q_OBJECT

public:
    explicit DenonCtrl(QWidget *parent = 0);
    ~DenonCtrl();

private:
    Ui::DenonCtrl *ui;
};

#endif // DENONCTRL_H
