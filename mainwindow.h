#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "thecalendar.h"
#include "dailyplan.h"
#include "ddlreminder.h"
#include "longtermproject.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    TheCalendar *calendar;
    DailyPlan *plan;
    ddlReminder *ddl;
    LongTermProject *myproject;
};
#endif // MAINWINDOW_H
