#include "interactivelist.h"
#include "ui_interactivelist.h"
#include "denonctrl.h"
#include <QListWidgetItem>

InteractiveList::InteractiveList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InteractiveList)
{
    ui->setupUi(this);

    QListWidgetItem *item = new QListWidgetItem;
    DenonCtrl *dCtrl = new DenonCtrl();
    item->setSizeHint(dCtrl->sizeHint());
    ui->denonList->addItem(item);
    ui->denonList->setItemWidget(item, dCtrl);

}

InteractiveList::~InteractiveList()
{
    delete ui;
}
