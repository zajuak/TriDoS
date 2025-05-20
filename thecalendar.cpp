#include "thecalendar.h"
#include "ui_thecalendar.h"
#include<QHBoxLayout>
#include<QLabel>
#include<QPushButton>
#include <QSpacerItem>
#include <QSizePolicy>
#include <QCalendarWidget>
#include <QDialog>
#include <QVBoxLayout>
#include <QDate>
#include <QTimer>
#include <QStringList>
#include <QRandomGenerator>
#include"dailysentencedialog.h"


TheCalendar::TheCalendar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TheCalendar)
{
    ui->setupUi(this);

    midnightTimer = new QTimer(this);
    connect(midnightTimer, &QTimer::timeout, this, &TheCalendar::checkAndUpdateButtons);

    // 设置初始日期
    lastUpdateDate = QDate::currentDate();

    // 立即执行一次更新
    updateAllDayButtons();

    // 启动定时器（每分钟检查一次，确保精确在0点触发）
    midnightTimer->start(60000); // 1分钟检查一次

    sentences << "生活就像一盒巧克力，你永远不知道下一颗是什么味道"
              << "代码写得好，bug少烦恼"
              << "Qt让GUI开发变得简单"
              << "每天学习一点点，进步不止一点点"
              << "坚持就是胜利"
              << "机会总是留给有准备的人";

}

TheCalendar::~TheCalendar()
{
    delete ui;
}

void TheCalendar::updateDayButton(QPushButton* button, Qt::DayOfWeek day)
{
    QDate today = QDate::currentDate();
    int currentDay = today.dayOfWeek();

    // 如果当前日期已经过了指定的星期几
    bool isDayPassed = (currentDay > day);

    QFont font = button->font();
    font.setStrikeOut(isDayPassed);
    button->setFont(font);

    // 设置不同颜色
    QPalette palette = button->palette();
    palette.setColor(QPalette::ButtonText, isDayPassed ? Qt::gray : Qt::black);
    button->setPalette(palette);
}

void TheCalendar::resetAllButtons()
{
    // 重置所有按钮样式
    QList<QPushButton*> dayButtons = {
        ui->Monday, ui->Tuesday, ui->Wednesday,
        ui->Thursday, ui->Friday, ui->Saturday, ui->Sunday
    };

    foreach (QPushButton* button, dayButtons) {
        QFont font = button->font();
        font.setStrikeOut(false);
        button->setFont(font);

        QPalette palette = button->palette();
        palette.setColor(QPalette::ButtonText, Qt::black);
        button->setPalette(palette);
    }
}

void TheCalendar::updateAllDayButtons()
{
    updateDayButton(ui->Monday, Qt::Monday);
    updateDayButton(ui->Tuesday, Qt::Tuesday);
    updateDayButton(ui->Wednesday, Qt::Wednesday);
    updateDayButton(ui->Thursday, Qt::Thursday);
    updateDayButton(ui->Friday, Qt::Friday);
    updateDayButton(ui->Saturday, Qt::Saturday);
    updateDayButton(ui->Sunday, Qt::Sunday);

    lastUpdateDate = QDate::currentDate();
}

void TheCalendar::checkAndUpdateButtons()
{
    QDateTime now = QDateTime::currentDateTime();

    // 检查是否到了新的一天（0点）
    if (now.time().hour() == 0 && now.time().minute() == 0) {
        // 检查是否是周日0点
        if (now.date().dayOfWeek() == Qt::Sunday && lastUpdateDate != now.date()) {
            resetAllButtons();
            qDebug() << "Sunday midnight - Reset all buttons";
        }

        // 更新所有按钮状态
        updateAllDayButtons();
        qDebug() << "Midnight update triggered at" << now.toString();
    }
}

class CalendarDialog : public QDialog {
public:
    CalendarDialog(QWidget *parent = nullptr) : QDialog(parent) {
        // 创建日历控件
        calendar = new QCalendarWidget(this);

        // 设置对话框布局
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(calendar);

        // 设置对话框属性
        setWindowTitle("选择日期");
        resize(400, 300);
    }

private:
    QCalendarWidget *calendar;
};

void TheCalendar::on_pushButton_2_clicked()
{
    QCalendarWidget *calendar = new QCalendarWidget(this);
    calendar->setWindowFlags(Qt::Window);
    calendar->setWindowTitle("日历");
    calendar->show();
}

void TheCalendar::on_dailySentence_clicked()
{
    int index = QRandomGenerator::global()->bounded(sentences.size());
    QString sentence = sentences.at(index);

    DailySentenceDialog *dialog = new DailySentenceDialog(sentence, this);
    dialog->setAttribute(Qt::WA_DeleteOnClose); // 关闭时自动删除
    dialog->show();

}

