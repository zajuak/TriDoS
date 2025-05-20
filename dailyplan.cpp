#include "dailyplan.h"
#include "ui_dailyplan.h"
#include "pomodorowidget.h"

DailyPlan::DailyPlan(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DailyPlan)
{
    ui->setupUi(this);
}

DailyPlan::~DailyPlan()
{
    delete ui;
}

void DailyPlan::on_pomodroButton_clicked()
{
    PomodoroWidget *pomodoro = new PomodoroWidget(nullptr);  // nullptr表示无父对象
    pomodoro->setWindowFlags(Qt::Window);
    pomodoro->setWindowTitle("番茄工作钟");
    pomodoro->setAttribute(Qt::WA_DeleteOnClose);  // 关闭时自动删除
    pomodoro->show();
}

