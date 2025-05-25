#include "calendardialog.h"
#include <QVBoxLayout>
#include <QMap>

CalendarDialog::CalendarDialog(QWidget *parent)
    : QDialog(parent),
    m_calendar(new QCalendarWidget(this))
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(m_calendar);

    setWindowTitle("DDL日历视图");
    resize(500, 400);

    setupDateFormats();
}

void CalendarDialog::setupDateFormats() {
    m_ddlFormat.setBackground(QColor(255, 255, 150)); // 浅黄色背景
    m_ddlFormat.setToolTip("有未完成事项"); // 默认提示
}

void CalendarDialog::markDDLDates(const QList<ddlItem>& items) {
    // 先按日期分组
    QMap<QDate, QList<ddlItem>> dateMap;
    for (const auto& item : items) {
        dateMap[item.deadline()].append(item);
    }

    // 清除所有旧标记
    m_calendar->setDateTextFormat(QDate(), QTextCharFormat());

    // 设置新标记和提示
    for (auto it = dateMap.begin(); it != dateMap.end(); ++it) {
        m_calendar->setDateTextFormat(it.key(), m_ddlFormat);

        // 为每个日期设置详细提示
        QString tooltip = "<b>" + it.key().toString("yyyy-MM-dd") + "</b><hr>";
        for (const auto& item : it.value()) {
            int daysLeft = QDate::currentDate().daysTo(item.deadline());
            QString dayStatus = daysLeft >= 0 ?
                                    QString("剩余%1天").arg(daysLeft) :
                                    "已过期";

            tooltip += QString("• %1 (%2)<br>")
                           .arg(item.title())
                           .arg(dayStatus);
        }

        // 获取现有的格式并更新tooltip
        QTextCharFormat format = m_calendar->dateTextFormat(it.key());
        format.setToolTip(tooltip);
        m_calendar->setDateTextFormat(it.key(), format);
    }
}
