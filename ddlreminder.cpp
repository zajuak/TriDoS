#include "ddlreminder.h"
#include "ui_ddlreminder.h"

ddlReminder::ddlReminder(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ddlReminder)
{
    ui->setupUi(this);
}

ddlReminder::~ddlReminder()
{
    delete ui;
}
