#ifndef DAILYPLAN_H
#define DAILYPLAN_H

#include <QWidget>
#include"pomodorowidget.h"
#include <qprogressbar.h>
#include <qdatetime.h>
#include <QWidget>
#include <QLabel>
#include <QList>
#include "dailydata.h"
#include <QDialog>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QMessageBox>

// 自定义对话框类
class InfoDialog : public QDialog {
    Q_OBJECT
public:
    explicit InfoDialog(QWidget *parent = nullptr);

    // 获取填写的信息
    QString Title();
    QString Detail();

private:
    QLineEdit *TitleEdit;
    QLineEdit *DetailEdit;
};


namespace Ui {
class DailyPlan;
class Issue;
}

class Issue : public QPushButton{
    Q_OBJECT

public:
    Issue(QString _Title = "noname", QString Detail = "nodetail", \
            QDateTime _Start = QDateTime::currentDateTime(), QDateTime _End = QDateTime::currentDateTime().addDays(1), \
                QString _Kind = "Today", bool _Finished = false, QWidget *parent = nullptr);
    ~Issue();
    void Emit_Issue();
    QString Get_Title();
    QString Get_Dura();
    QString Get_Detail();
    QString Get_Kind();
    Qt::CheckState Get_State();
    void Set_State(const bool ck);
    dailydata IssuetoData();


private slots:
signals:
    void Show_Issue(Issue* Showed);


private:
    QString IssueTitle;
    QDateTime IssueStart;
    QDateTime IssueEnd;
    QString IssueDetail;
    bool IssueFinished;
    QString IssueKind;
};

class DailyPlan : public QWidget
{
    Q_OBJECT

public:
    DailyPlan(QWidget *parent = nullptr,QString _Date= QDateTime::currentDateTime().date().toString("yyyy-MM-dd"));
    ~DailyPlan();
    void Renew_DTime();
    void Load_Schedule();
    void Add_Issue(dailydata data);
    void Add_Habit(dailydata data);
    void Show_Detail(Issue* Showed);
    void Delete_Issue();
    void CancelorClear();
    void IssueSaveToFile(const QString filename);
    void HabitSaveToFile(const QString filename);
    void LoadFromFile(const QString &filename);
    void Change_Table();
    void Change_Schedule();
    QString Date;
    void setDate(const QString& newDate);


private slots:
    void on_pomodroButton_clicked();
    void on_checkBox_checkStateChanged(const Qt::CheckState &arg1);
    void showDialog();

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
    std::vector<Issue*> ScheduleButtons;
    static std::vector<Issue*> HabitButtons;
    QList<dailydata> storedata;
    QPushButton ModiIssue;
    QString IssueOnShow;

};


#endif // DAILYPLAN_H
