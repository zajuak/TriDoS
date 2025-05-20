#include "weekbuttongroup.h"
#include "ui_weekbuttongroup.h"


#include <QHBoxLayout>
#include <QTimer>

WeekButtonGroup::WeekButtonGroup(QWidget *parent) : QWidget(parent) {
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setSpacing(10);
    layout->setContentsMargins(5, 5, 5, 5);

    // 创建7个圆形按钮
    for (int i = 0; i < 7; ++i) {
        QPushButton *btn = new QPushButton(dayNames[i], this);
        btn->setFixedSize(60, 60); // 固定为圆形尺寸
        btn->setCheckable(true);

        // 圆形样式
        btn->setStyleSheet(R"(
            QPushButton {
                border-radius: 30px;
                border: 2px solid #3498db;
                background: #f8f9fa;
                font-size: 14px;
            }
            QPushButton:checked {
                background: #e3f2fd;
                border-color: #1e88e5;
            }
            QPushButton:pressed {
                background: #bbdefb;
            }
        )");

        connect(btn, &QPushButton::clicked, this, &WeekButtonGroup::handleDayClick);
        dayButtons.append(btn);
        layout->addWidget(btn);
    }

    // 每天凌晨自动更新
    QTimer *dailyTimer = new QTimer(this);
    connect(dailyTimer, &QTimer::timeout, [this](){
        if (QTime::currentTime().hour() == 0) // 零点触发
            updateWeek(QDate::currentDate());
    });
    dailyTimer->start(3600000); // 每小时检查一次
}

void WeekButtonGroup::updateWeek(const QDate &currentDate) {
    QDate monday = currentDate.addDays(-(currentDate.dayOfWeek() - 1));
    weekDates.clear();

    for (int i = 0; i < 7; ++i) {
        QDate day = monday.addDays(i);
        weekDates.append(day);

        // 设置删除线样式
        QString style = dayButtons[i]->styleSheet();
        if (day < QDate::currentDate()) {
            style += "text-decoration: line-through; color: #95a5a6;";
        } else {
            style.replace("text-decoration: line-through;", "");
            style.replace("color: #95a5a6;", "");
        }
        dayButtons[i]->setStyleSheet(style);

        // 显示日期提示
        dayButtons[i]->setToolTip(day.toString("yyyy-MM-dd dddd"));
    }
}

void WeekButtonGroup::handleDayClick() {
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    int index = dayButtons.indexOf(btn);
    qDebug() << "选中:" << weekDates[index].toString("yyyy-MM-dd");
}

WeekButtonGroup::~WeekButtonGroup()
{
    delete ui;
}
