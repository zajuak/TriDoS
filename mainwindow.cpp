#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSplitter>  // 核心头文件
#include <QHBoxLayout> // 如需配合布局使用
#include "weekbuttongroup.h"
#include <QPalette>
#include <QColor>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //创建四个部分的对象
    TheCalendar *calendar=new TheCalendar(this);
    DailyPlan *plan=new DailyPlan(this);
    ddlReminder *ddl=new ddlReminder(this);
    LongTermProject *myproject=new LongTermProject(this);
    myproject->setDDLReminder(ddl);
    calendar->set_dailyplan(plan);
    // 在初始化代码中设置
    QPalette calendarPalette = calendar->palette();
    calendarPalette.setColor(QPalette::Window, QColor(255, 255, 255, 180));
    calendar->setAutoFillBackground(true);
    calendar->setPalette(calendarPalette);

    // 设置Plan背景 - 透明浅蓝色 (RGBA: 173,216,230,180)
    QPalette planPalette = plan->palette();
    planPalette.setColor(QPalette::Window, QColor(173, 216, 230, 180));
    plan->setAutoFillBackground(true);
    plan->setPalette(planPalette);

    // 设置DDL背景 - 透明白色 (RGBA: 255,255,255,180)
    QPalette ddlPalette = ddl->palette();
    ddlPalette.setColor(QPalette::Window, QColor(255, 255, 255, 180));
    ddl->setAutoFillBackground(true);
    ddl->setPalette(ddlPalette);

    // 设置MyProject背景 - 透明白色 (RGBA: 255,255,255,180)
    QPalette projectPalette = myproject->palette();
    projectPalette.setColor(QPalette::Window, QColor(255, 255, 255, 180));
    myproject->setAutoFillBackground(true);
    myproject->setPalette(projectPalette);

    //创建底层三个Widget的分割器
    QSplitter *bottomSplitter=new QSplitter(Qt::Horizontal);
    QSplitter *bottomRightSplitter=new QSplitter(Qt::Vertical);
    bottomRightSplitter->addWidget(ddl);
    bottomRightSplitter->addWidget(myproject);
    bottomSplitter->addWidget(plan);
    bottomSplitter->addWidget(bottomRightSplitter);
    //创建主垂直分割器
    QSplitter *mainSplitter=new QSplitter(Qt::Vertical);

    mainSplitter->addWidget(calendar);
    mainSplitter->addWidget(bottomSplitter);
    //设置主窗口中心部件
    setCentralWidget(mainSplitter);
    //设置四个区域的比例
    mainSplitter->setSizes({height()/6,height()*5/6});
    bottomSplitter->setSizes({width()*2/3,width()/3});
    bottomRightSplitter->setSizes({height()*2/5,height()*3/5});





}

MainWindow::~MainWindow()
{
    delete ui;
}
