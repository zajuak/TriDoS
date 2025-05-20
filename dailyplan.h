#ifndef DAILYPLAN_H
#define DAILYPLAN_H

#include <QWidget>
#include"pomodorowidget.h"

namespace Ui {
class DailyPlan;
}

class DailyPlan : public QWidget
{
    Q_OBJECT

public:
    explicit DailyPlan(QWidget *parent = nullptr);
    ~DailyPlan();

private slots:
    void on_pomodroButton_clicked();

private:
    Ui::DailyPlan *ui;
    PomodoroWidget *m_pomodoroWindow = nullptr;
};

#endif // DAILYPLAN_H
