#ifndef WEEKBUTTONGROUP_H
#define WEEKBUTTONGROUP_H

#include <QWidget>
#include <QPushButton>
#include <QDate>

namespace Ui {
class WeekButtonGroup;
}

class WeekButtonGroup : public QWidget
{
    Q_OBJECT

public:
    explicit WeekButtonGroup(QWidget *parent = nullptr);
    ~WeekButtonGroup();
    void updateWeek(const QDate &currentDate);

private slots:
    void handleDayClick();

private:
    Ui::WeekButtonGroup *ui;
    QVector<QPushButton*> dayButtons;
    QVector<QDate> weekDates;
    QStringList dayNames = {"周一", "周二", "周三", "周四", "周五", "周六", "周日"};
};

#endif // WEEKBUTTONGROUP_H
