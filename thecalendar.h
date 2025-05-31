#ifndef THECALENDAR_H
#define THECALENDAR_H

#include <QWidget>
#include<QPushButton>
#include<Qdate>
#include <QStringList>
#include <QRandomGenerator>
#include<QSettings>
#include"dailyplan.h"
class Ui_TheCalendar;
class CalendarDialog;
class TheCalendar : public QWidget
{
    Q_OBJECT

public:
    explicit TheCalendar(QWidget *parent = nullptr);

    ~TheCalendar();
    void set_dailyplan(DailyPlan*dailyplan);


private slots:
    void on_pushButton_2_clicked();
    void updateAllDayButtons();
    void checkAndUpdateButtons();
    void on_dailySentence_clicked();


private:
    Ui_TheCalendar *ui;
    void updateDayButton(QPushButton* button, Qt::DayOfWeek day);
    void resetAllButtons();
    QTimer* midnightTimer;
    QDate lastUpdateDate;

    void getRandomSentence();
    QStringList sentences;
    QString m_todaySentence;
    QDate m_lastSentenceDate;

    void saveDailySentence();
    void loadDailySentence();
    DailyPlan*m_dailyplan;

};




#endif // THECALENDAR_H
