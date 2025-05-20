#ifndef THECALENDAR_H
#define THECALENDAR_H

#include <QWidget>
#include<QPushButton>
#include<Qdate>
#include <QStringList>
#include <QRandomGenerator>



class Ui_TheCalendar;

class TheCalendar : public QWidget
{
    Q_OBJECT

public:
    explicit TheCalendar(QWidget *parent = nullptr);

    ~TheCalendar();


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


};




#endif // THECALENDAR_H
