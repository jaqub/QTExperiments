#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Qtimer;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected slots:
    void timeout(void);
    void enableTimer(bool enable);
    void resetTimer(void);

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    unsigned int cnt;
};
#endif // MAINWINDOW_H
