#include "dailyplan.h"
#include "ui_dailyplan.h"
#include "pomodorowidget.h"
#include <QDateTime>
#include <QString>
//更新不同的事件，点击显示细节，点击修改计划(返回事件名字Qstring作为索引),默认显示当天,看不同日子的计划只需要切换不同的dailyplan
Issue::Issue(QPushButton *parent, QString _Title, QString _Detail, QDateTime _Start, QDateTime _End)
    :QPushButton(parent)
    ,IssueTitle(_Title)
    ,IssueStart(_Start)
    ,IssueEnd(_End)
    ,IssueDetial(("\t"+_Detail))
{
    connect(this,&QPushButton::clicked,this,&Issue::Emit_Issue);
    this->setText(IssueTitle);
}
Issue::~Issue(){

}
void Issue::Emit_Issue(){
    emit this->Show_Issue(this);
}
QString Issue::Get_Title(){
    return this->IssueTitle;
}
QString Issue::Get_Dura(){
    QString tmp="";
    tmp=this->IssueStart.toString("yyyy-MM-dd hh:mm:ss");
    tmp+="---";
    tmp+=this->IssueEnd.toString("yyyy-MM-dd hh:mm::ss");
    return tmp;
}
QString Issue::Get_Detail(){
    return this->IssueDetial;
}

DailyPlan::DailyPlan(QWidget *parent,QString _Date)
    : QWidget(parent)
    , ui(new Ui::DailyPlan)
    ,Date(_Date)
{
    //init
    ui->setupUi(this);
    IssueOnShow="";
    ui->IssueTitle->setText("null");
    ui->IssueDura->setText("null");
    ui->IssueDetail->setText("null");
    ui->DayOnShow->setText(Date);
    //QDateTime CurrentTimer=QDateTime::currentDateTime();
    //QString TimeString =
    //StartDTime();
    //connect(ui->StartDTime,&QPushButton::clicked,this,&DailyPlan::StartDTime());
    //this->DTimer = new QTimer(this);

    //start Timer
    DTimer = new QTimer(this);
    connect(DTimer,&QTimer::timeout,this,&DailyPlan::Renew_DTime);
    DTimer->start(1000);

    /*
    ui->ModiIssue->hide();
    ui->IssueDetail->hide();
    ui->IssueTitle->hide();
    ui->IssueDura->hide();
    */
    ScheduleButtons.clear();
    //debug for addissue and scheduleshow
    /*
    ScheduleButtons.push_back(ui->Issue1);
    ScheduleButtons.push_back(ui->Issue2);
    ScheduleButtons.push_back(ui->Issue3);
    ScheduleButtons.push_back(ui->Issue4);
    ScheduleButtons.push_back(ui->Issue5);
    ScheduleButtons.push_back(ui->Issue6);
    */
    Issue* newissue1= new Issue(nullptr,"newissue1","nononono");
    ScheduleButtons.push_back(newissue1);
    connect(newissue1,&Issue::Show_Issue,this,&DailyPlan::Show_Detail);
    Issue* newissue2= new Issue(nullptr,"newissue2","yesyesyes");
    ScheduleButtons.push_back(newissue2);
    connect(newissue2,&Issue::Show_Issue,this,&DailyPlan::Show_Detail);
    Issue* newissue3= new Issue(nullptr,"newissue3","ohhhhhhhh");
    ScheduleButtons.push_back(newissue3);
    connect(newissue3,&Issue::Show_Issue,this,&DailyPlan::Show_Detail);

    //load schedule
    Load_Schedule();
    //enable modify
    connect(ui->ModiIssue,&QPushButton::clicked,this,&DailyPlan::Modi_Issue);
}

DailyPlan::~DailyPlan()
{
    delete ui;
}

void DailyPlan::Renew_DTime()
{
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QTime currentTime=currentDateTime.time();
    int tmpprogress=(currentTime.hour()*60+currentTime.minute())*100/1440;
    QString timeString = currentDateTime.toString("yyyy-MM-dd hh:mm:ss");//时间转字符串
    ui->NowTime->setText(timeString);
    ui->TimeProgress->setValue(tmpprogress);
    //ui->TimeProgress->setTextVisible(false);
}

void DailyPlan::Load_Schedule(){
    //读入当天计划
    //ScheduleButtons.push_back(ui->Issue1);
    //ScheduleButtons.push_back(ui->Issue2);
    //ScheduleButtons.push_back(ui->Issue3);
    //ScheduleButtons.push_back(ui->Issue4);
    //ScheduleButtons.push_back(ui->Issue5);
    //ScheduleButtons.push_back(ui->Issue6);
    //ScheduleButtons.clear();
    for(auto i=ScheduleButtons.begin();i!=ScheduleButtons.end();i++){
        ui->ScheduleLayout->insertWidget(ui->ScheduleLayout->count(), (*i));
    }
}

void DailyPlan::Add_Issue(Issue* NewIssue){
    ScheduleButtons.push_back(NewIssue);
    connect(NewIssue,&Issue::Show_Issue,this,&DailyPlan::Show_Detail);
}

void DailyPlan::Show_Detail(Issue* Showed){
    ui->IssueTitle->setText(Showed->Get_Title());
    ui->IssueDura->setText(Showed->Get_Dura());
    ui->IssueDetail->setText(Showed->Get_Detail());
    IssueOnShow=Showed->Get_Title();
}

void DailyPlan::Modi_Issue(){
    if(IssueOnShow!=""){
        emit Modi_Signal(IssueOnShow);
    }
}
void DailyPlan::on_pomodroButton_clicked()
{
    PomodoroWidget *pomodoro = new PomodoroWidget(nullptr);  // nullptr表示无父对象
    pomodoro->setWindowFlags(Qt::Window);
    pomodoro->setWindowTitle("番茄工作钟");
    pomodoro->setAttribute(Qt::WA_DeleteOnClose);  // 关闭时自动删除
    pomodoro->show();
}





