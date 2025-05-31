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
#include <QTimer>
#include <QStringList>
#include <QRandomGenerator>
#include"dailysentencedialog.h"
#include"ddlreminder.h"
#include"mycalendar.h"


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
              << "向春天走去，别烂在过去和梦里"
              << "用舍由时，行藏在我"
              << "当你为错过太阳而哭泣时，那么你也将失去群星了"
              << "推石上山这场搏斗本身，就足以充实一颗人心"
              << "此心安处是吾乡";

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

void TheCalendar::set_dailyplan(DailyPlan*dailyplan)
{
    m_dailyplan=dailyplan;
}


void TheCalendar::on_pushButton_2_clicked()
{
    ddlReminder* reminder = new ddlReminder();
    MyCalendar* calendar = new MyCalendar(reminder,m_dailyplan);

    // 当需要显示日历时
    calendar->showCalendar();
}

void TheCalendar::on_dailySentence_clicked()
{
    QDate today = QDate::currentDate();

    // 需要重新选择句子的情况：
    // 1. 还没有选择过句子(m_todaySentence为空)
    // 2. 上次选择不是今天
    if (m_todaySentence.isEmpty() || m_lastSentenceDate != today) {
        int index = QRandomGenerator::global()->bounded(sentences.size());
        m_todaySentence = sentences.at(index);
        m_lastSentenceDate = today;
        saveDailySentence();
    }

    DailySentenceDialog *dialog = new DailySentenceDialog(m_todaySentence, this);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    QString title = (m_lastSentenceDate == QDate::currentDate())
                        ? "今日箴言"
                        : "新的一天，新的箴言";
    dialog->setWindowTitle(title);
    dialog->show();

}

void TheCalendar::saveDailySentence()
{
    QSettings settings("MyApp", "DailySentence");
    settings.beginGroup("DailySentence");
    settings.setValue("text", m_todaySentence);
    settings.setValue("date", m_lastSentenceDate);
    settings.endGroup();
}

void TheCalendar::loadDailySentence()
{
    QSettings settings("MyApp", "DailySentence");
    settings.beginGroup("DailySentence");
    m_todaySentence = settings.value("text").toString();
    m_lastSentenceDate = settings.value("date").toDate();
    settings.endGroup();

    // 如果存储的日期不是今天，则视为无效
    if (m_lastSentenceDate != QDate::currentDate()) {
        m_todaySentence.clear();
    }
}
