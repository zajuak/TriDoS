#ifndef DAILYPLAN_H
#define DAILYPLAN_H

#include <QWidget>
#include"pomodorowidget.h"
#include <qprogressbar.h>
#include <qdatetime.h>
namespace Ui {
class DailyPlan;
class Issue;
}

class Issue : public QPushButton{
    Q_OBJECT

public:
    Issue(QPushButton *parent = nullptr,QString _Title = "noname",QString Detail = "nodetail",QDateTime _Start = QDateTime::currentDateTime(),QDateTime _End = QDateTime::currentDateTime().addDays(1));
    ~Issue();
    void Emit_Issue();
    QString Get_Title();
    QString Get_Dura();
    QString Get_Detail();


private slots:
signals:
    void Show_Issue(Issue* Showed);


private:
    QString IssueTitle;
    QDateTime IssueStart;
    QDateTime IssueEnd;
    QString IssueDetial;
};

class DailyPlan : public QWidget
{
    Q_OBJECT

public:
    DailyPlan(QWidget *parent = nullptr,QString _Date= QDateTime::currentDateTime().date().toString("yyyy-MM-dd"));
    ~DailyPlan();
    void Renew_DTime();
    void Load_Schedule();
    void Add_Issue(Issue* NewIssue);
    void Show_Detail(Issue* Showed);
    void Modi_Issue();


private slots:
    void on_pomodroButton_clicked();
signals:
    void Modi_Signal(QString ToModi);

private:
    Ui::DailyPlan *ui;
    PomodoroWidget *m_pomodoroWindow = nullptr;
    QLabel IssueTitle;
    QLabel IssueDetail;
    QLabel IssueDura;
    QLabel NowTime;
    QProgressBar TimeProcess;
    QTimer* DTimer;
    QDateTime DTime;
    std::vector<QPushButton*> ScheduleButtons;
    QPushButton ModiIssue;
    QString IssueOnShow;
    QString Date;
};


#endif // DAILYPLAN_H
