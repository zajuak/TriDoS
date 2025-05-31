#include "dailyplan.h"
#include "ui_dailyplan.h"
#include "pomodorowidget.h"
#include <QDateTime>
#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDir>
#include <QMessageBox>
//更新不同的事件，点击显示细节，点击修改计划(返回事件名字Qstring作为索引),默认显示当天,看不同日子的计划只需要切换不同的dailyplan
//加一个属性描述，完成情况的layout，给事件列表改成滚屏，习惯打卡事件储存（静态向量、录入函数）
//给几个按钮加一下信号槽(今日事:复用一下longtermproject,(delete,modify)：对接longterm，返回字符串作为索引)
//事件的当日完成情况在本类中更改，编辑事件（题目，详情，事件，类型）未提供更改，完成情况的数值
std::vector<Issue*> DailyPlan::HabitButtons;
Issue::Issue(QString _Title, QString _Detail, QDateTime _Start, QDateTime _End, QString _Kind, bool _Finished, QWidget *parent )
    :QPushButton(parent)
    ,IssueTitle(_Title)
    ,IssueStart(_Start)
    ,IssueEnd(_End)
    ,IssueDetail((_Detail))
    ,IssueFinished(_Finished)
    ,IssueKind(_Kind)
{
    connect(this,&QPushButton::clicked,this,&Issue::Emit_Issue);
    this->setText(IssueTitle);
}
Issue::~Issue(){
    delete this;
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
    return this->IssueDetail;
}
QString Issue::Get_Kind(){
    return this->IssueKind;
}
Qt::CheckState Issue::Get_State(){
    if(this->IssueFinished)
        return Qt::Checked;
    else
        return Qt::Unchecked;
}
void Issue::Set_State(const bool ck){
    this->IssueFinished=ck;
    return;
}
dailydata Issue::IssuetoData(){
    dailydata tmp(IssueTitle,IssueDetail,IssueStart,IssueEnd,IssueKind,IssueFinished);
    return tmp;
}
void DailyPlan::setDate(const QString& newDate) {
    if (Date != newDate) {
        // 1. 保存当前数据
        IssueSaveToFile(Date + ".json");

        // 2. 更新日期
        Date = newDate;
        ui->DayOnShow->setText(Date);

        // 3. 重新加载数据
        ScheduleButtons.clear();
        Load_Schedule();
        Change_Schedule();  // 强制刷新UI
    }
}
DailyPlan::DailyPlan(QWidget *parent,QString _Date)
    : QWidget(parent)
    ,Date(_Date)
    , ui(new Ui::DailyPlan)
{
    //init
    ui->setupUi(this);
    //init detail
    IssueOnShow="";

    ui->IssueTitle->setText("null");
    ui->IssueDura->setText("null");
    ui->IssueDetail->setText("null");
    ui->DayOnShow->setText(Date);
    ui->Kinds->setText("No Kind");
    ui->checkBox->setCheckState(Qt::Unchecked);
    //QDateTime CurrentTimer=QDateTime::currentDateTime();
    //QString TimeString =
    //StartDTime();
    //connect(ui->StartDTime,&QPushButton::clicked,this,&DailyPlan::StartDTime());
    //this->DTimer = new QTimer(this);

    //start Timer
    DTimer = new QTimer(this);
    connect(DTimer,&QTimer::timeout,this,&DailyPlan::Renew_DTime);
    DTimer->start(1000);
    //start layout
    /*
    ui->ModiIssue->hide();
    ui->IssueDetail->hide();
    ui->IssueTitle->hide();
    ui->IssueDura->hide();
    */

    //load schedule
    Load_Schedule();
    ui->HabitOrToday->setText("日程表");
    ui->AddForToday->setText("创建日程");
    Change_Schedule();
    //dailydata newdata("well");
    //Add_Issue(newdata);
    //enable transtable
    connect(ui->HabitOrToday,&QPushButton::clicked,this,&DailyPlan::Change_Table);
    //enable modify and create
    connect(ui->AddForToday, &QPushButton::clicked, this, &DailyPlan::showDialog);
    //enable delete
    connect(ui->DeleteIssue,&QPushButton::clicked,this,&DailyPlan::Delete_Issue);
    //enable clearandcancle
    connect(ui->ModiIssue,&QPushButton::clicked,this,&DailyPlan::CancelorClear);
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
    ScheduleButtons.clear();
    HabitButtons.clear();

    QString filename = Date+".json";
    storedata.clear();
    LoadFromFile(filename);
    if(!storedata.empty()){
        for(dailydata &item : storedata){
            Issue* tmp = new Issue(item.title(),item.detail(),item.start(),item.end(),item.kind(),item.finished(),nullptr);
            connect(tmp,&Issue::Show_Issue,this,&DailyPlan::Show_Detail);
            ScheduleButtons.push_back(tmp);
        }
    }
    filename = "habit.json";
    storedata.clear();
    LoadFromFile(filename);
    if(!storedata.empty()){
        for(dailydata &item : storedata){
            Issue* tmp = new Issue(item.title(),item.detail(),item.start(),item.end(),item.kind(),item.finished(),nullptr);
            connect(tmp,&Issue::Show_Issue,this,&DailyPlan::Show_Detail);
            HabitButtons.push_back(tmp);
        }
    }
    storedata.clear();
}
void DailyPlan::Change_Schedule(){//全面更新schedule
    int cnt=0;
    QVBoxLayout* newLayout = new QVBoxLayout;
    if(ui->HabitOrToday->text() == "日程表"){
        for(auto i=ScheduleButtons.begin();i!=ScheduleButtons.end();i++){
            (*i)->setMinimumHeight(30);
            (*i)->sizePolicy().setHorizontalPolicy(QSizePolicy::Preferred);
            newLayout->insertWidget(newLayout->count(), (*i));
            cnt++;
        }
    }
    else{
        for(auto i=HabitButtons.begin();i!=HabitButtons.end();i++){
            (*i)->setMinimumHeight(30);
            (*i)->sizePolicy().setHorizontalPolicy(QSizePolicy::Preferred);
            newLayout->insertWidget(newLayout->count(), (*i));
            cnt++;
        }
    }

    QLayout *oldLayout = ui->ScheduleContent->layout();
    if (oldLayout) {
        while (QLayoutItem *item = oldLayout->takeAt(0)) {
            if (item->widget()) {
                item->widget()->setParent(nullptr);
            }
            delete item;
        }
        delete oldLayout;
    }
    // 设置新布局
    ui->ScheduleContent->setLayout(newLayout);

    ui->ScheduleContent->resize(250,50*cnt);
    ui->ScheduleScroll->viewport()->update();
}

void DailyPlan::Change_Table(){
    if(ui->HabitOrToday->text() == "日程表"){
        ui->HabitOrToday->setText("习惯表");
        ui->AddForToday->setText("创建习惯");
        Change_Schedule();
        return;
    }
    else{
        ui->HabitOrToday->setText("日程表");
        ui->AddForToday->setText("创建日程");
        Change_Schedule();
        return;
    }
}
void DailyPlan::IssueSaveToFile(const QString filename)
{
    QJsonArray jsonArray;
    for (auto i = ScheduleButtons.begin();i!= ScheduleButtons.end();i++) {
        dailydata tmp = (*i)->IssuetoData();
        jsonArray.append(tmp.toJson());
    }

    QJsonDocument doc(jsonArray);
    QFile file(filename);

    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "无法打开文件用于写入:" << filename;
        return;
    }

    file.write(doc.toJson());
    file.close();

    qDebug() << "Daily数据已保存到:" << filename;
}
void DailyPlan::HabitSaveToFile(const QString filename)
{
    QJsonArray jsonArray;
    for (auto i = HabitButtons.begin();i!= HabitButtons.end();i++) {
        dailydata tmp = (*i)->IssuetoData();
        jsonArray.append(tmp.toJson());
    }

    QJsonDocument doc(jsonArray);
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "无法打开文件用于写入:" << filename;
        return;
    }

    file.write(doc.toJson());
    file.close();

    qDebug() << "Habit数据已保存到:" << filename;
}
void DailyPlan::LoadFromFile(const QString &filename)
{
    QFile file(filename);
    if (!file.exists()) {
        qDebug() << "保存文件不存在，将创建新文件";
        return;
    }

    if (!file.open(QIODevice::ReadWrite)) {
        qWarning() << "无法打开文件用于读取:" << filename;
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isNull() || !doc.isArray()) {
        qWarning() << "文件格式无效:" << filename;
        storedata.clear();
        return;
    }

    storedata.clear();
    QJsonArray jsonArray = doc.array();
    for (const QJsonValue &value : jsonArray) {
        if (value.isObject()) {
            dailydata item = dailydata::fromJson(value.toObject());
            if (!item.title().isEmpty()) {  // 跳过无效条目
                storedata.append(item);
            }
        }
    }

    qDebug() << "从文件加载了" << storedata.size() << "个daily/habit事项";
}

void DailyPlan::Add_Issue(dailydata data){
    Issue* NewIssue = new Issue(data.title(),data.detail(),data.start(),data.end(),data.kind(),data.finished(),ui->ScheduleContent);
    ScheduleButtons.push_back(NewIssue);
    connect(NewIssue,&Issue::Show_Issue,this,&DailyPlan::Show_Detail);
    IssueSaveToFile(Date+".json");
    NewIssue->setMinimumHeight(30);
    NewIssue->sizePolicy().setHorizontalPolicy(QSizePolicy::Preferred);
    Change_Schedule();
}

void DailyPlan::Add_Habit(dailydata data){
    Issue* NewHabit = new Issue(data.title(),data.detail(),data.start(),data.end(),data.kind(),data.finished(),ui->ScheduleContent);
    HabitButtons.push_back(NewHabit);
    connect(NewHabit,&Issue::Show_Issue,this,&DailyPlan::Show_Detail);
    HabitSaveToFile("habit.json");
    NewHabit->setMinimumHeight(30);
    NewHabit->sizePolicy().setHorizontalPolicy(QSizePolicy::Preferred);
    Change_Schedule();
}

void DailyPlan::Show_Detail(Issue* Showed){
    ui->IssueTitle->setText(Showed->Get_Title());
    ui->IssueDura->setText(Showed->Get_Dura());
    ui->IssueDetail->setText(Showed->Get_Detail());
    IssueOnShow=Showed->Get_Title();
    ui->Kinds->setText(Showed->Get_Kind());
    ui->checkBox->setCheckState(Showed->Get_State());
}

void DailyPlan::CancelorClear(){
    if(ui->ModiIssue->text() == "Clear"){
        ui->IssueTitle->setText("null");
        ui->IssueDura->setText("null");
        ui->IssueDetail->setText("null");
        ui->Kinds->setText("No Kind");
        ui->checkBox->setCheckState(Qt::Unchecked);
    }
    else{
        ui->DeleteIssue->setText("Delete");
        ui->ModiIssue->setText("Clear");
    }
}

void DailyPlan::Delete_Issue(){
    /*
    if(IssueOnShow!=""){
        emit Modi_Signal(IssueOnShow);
    }
    */
    if (ui->DeleteIssue->text() == "Delete"){
        ui->DeleteIssue->setText("Confirm Delete");
        ui->ModiIssue->setText("Cancel");
    }
    else{
        ui->DeleteIssue->setText("Delete");
        ui->ModiIssue->setText("Clear");
        for(auto i = ScheduleButtons.begin();i!=ScheduleButtons.end();i++){
            if((*i)->Get_Title()==ui->IssueTitle->text()){
                ScheduleButtons.erase(i);
                ui->ScheduleContent->layout()->removeWidget((*i));
                Change_Schedule();
                ui->IssueTitle->setText("null");
                ui->IssueDura->setText("null");
                ui->IssueDetail->setText("null");
                ui->Kinds->setText("No Kind");
                ui->checkBox->setCheckState(Qt::Unchecked);
                ui->ScheduleScroll->viewport()->update();
                break;
            }
        }
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

void DailyPlan::on_checkBox_checkStateChanged(const Qt::CheckState &arg1)
{
    for(auto i=ScheduleButtons.begin();i!=ScheduleButtons.end();i++){
        if((*i)->text() == IssueOnShow){
            (*i)->Set_State(arg1);
        }
    }
}


void DailyPlan::showDialog() {
    InfoDialog dialog(this);
    QString title;
    QString detail = dialog.Detail();

    if (dialog.exec() == QDialog::Accepted) {
        // 获取输入内容
        title = dialog.Title();
        detail = dialog.Detail();
        // 这里可以添加处理数据的代码
        qDebug() << "title:" << title;
        qDebug() << "detail:" << detail;
        if(ui->AddForToday->text()=="创建日程"){
            dailydata tmp(title,detail);
            Add_Issue(tmp);
        }
        else{
            dailydata tmp(title,detail,QDateTime::currentDateTime(),QDateTime::currentDateTime(),"Habit");
            Add_Habit(tmp);
        }
    }
}

InfoDialog::InfoDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("填写信息");
    setFixedSize(200, 200);

    // 创建表单布局
    QFormLayout *formLayout = new QFormLayout;

    // 添加输入字段
    TitleEdit = new QLineEdit;
    DetailEdit = new QLineEdit;

    formLayout->addRow("标题:", TitleEdit);
    formLayout->addRow("细节:", DetailEdit);

    // 创建确认按钮
    QDialogButtonBox *buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel
    );
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    // 设置主布局
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);
}

QString InfoDialog::Title() { return TitleEdit->text(); }
QString InfoDialog::Detail() { return DetailEdit->text(); }
