#include "longtermproject.h"
#include "ui_longtermproject.h"

LongTermProject::LongTermProject(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LongTermProject)
{
    ui->setupUi(this);
}

LongTermProject::~LongTermProject()
{
    delete ui;
}
