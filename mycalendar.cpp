#include "mycalendar.h"
// thecalendar.cpp
#include"mycalendar.h"
#include "calendardialog.h"
#include <QDebug>

MyCalendar::MyCalendar(ddlReminder* ddlManager,DailyPlan*dailyplan, QWidget *parent)
    : QWidget(parent),
    m_calendarDialog(new CalendarDialog(dailyplan,this)),
    m_ddlManager(ddlManager),
    m_dailyplan(dailyplan)
{
    // 连接ddlReminder的数据变化信号
    connect(m_ddlManager, &ddlReminder::dataChanged,
            this, &MyCalendar::updateCalendarDisplay);

    // 初始更新一次
    updateCalendarDisplay();
}

MyCalendar::~MyCalendar() {
    delete m_calendarDialog;
}

void MyCalendar::showCalendar() {
    m_calendarDialog->show();
}

void MyCalendar::updateCalendarDisplay() {
    // 获取所有DDL日期
    QList<QDate> dates;
    for (const auto& item : m_ddlManager->getAllItems()) {
        dates.append(item.deadline());
    }

    // 更新日历显示
    m_calendarDialog->markDDLDates(m_ddlManager->getAllItems());

    qDebug() << "日历已更新，共显示" << dates.size() << "个DDL日期";
}
