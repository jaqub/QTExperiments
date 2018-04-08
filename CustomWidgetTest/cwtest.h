#ifndef CWTEST_H
#define CWTEST_H

#include <QWidget>

namespace Ui {
class CWTest;
}

class CWTest : public QWidget
{
    Q_OBJECT

public:
    explicit CWTest(QWidget *parent = 0);
    ~CWTest();

private:
    Ui::CWTest *ui;
};

#endif // CWTEST_H
