#ifndef CALENDARDIALOG_H
#define CALENDARDIALOG_H

#include <QDialog>
#include <QCalendarWidget>
#include<QTextCharFormat>
#include"ddlitem.h"

class CalendarDialog : public QDialog {
    Q_OBJECT
public:
    explicit CalendarDialog(QWidget *parent = nullptr);
    void markDDLDates(const QList<ddlItem>& items);

private:
    void setupDateFormats();
    QString createDateTooltip(const QList<ddlItem>& items);
    QCalendarWidget* m_calendar;
    QTextCharFormat m_ddlFormat;
};
#endif // CALENDARDIALOG_H
