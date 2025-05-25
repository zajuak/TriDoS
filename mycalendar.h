#ifndef MYCALENDAR_H
#define MYCALENDAR_H

#include <QWidget>
#include "ddlreminder.h"  // 包含你的ddlReminder头文件

class CalendarDialog;  // 前向声明

class MyCalendar : public QWidget {
    Q_OBJECT
public:
    explicit MyCalendar(ddlReminder* ddlManager, QWidget *parent = nullptr);
    ~MyCalendar();

    void showCalendar();

private slots:
    void updateCalendarDisplay();

private:
    CalendarDialog* m_calendarDialog;
    ddlReminder* m_ddlManager;  // 持有ddlReminder的指针
};
#endif // MYCALENDAR_H
