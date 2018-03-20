#ifndef INTERACTIVELIST_H
#define INTERACTIVELIST_H

#include <QWidget>

namespace Ui {
class InteractiveList;
}

class InteractiveList : public QWidget
{
    Q_OBJECT

public:
    explicit InteractiveList(QWidget *parent = 0);
    ~InteractiveList();

private:
    Ui::InteractiveList *ui;
};

#endif // INTERACTIVELIST_H
