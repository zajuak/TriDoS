#include "ddlwidget.h"
#include<QDate>
#include<QMouseEvent>
ddlWidget::ddlWidget(const ddlItem&item,QWidget* parent): QWidget(parent),m_item(item){
    QVBoxLayout* layout = new QVBoxLayout(this);

    m_titleLabel = new QLabel(item.title(), this);
    m_titleLabel->setStyleSheet("font-weight: bold; font-size: 14px;");

    m_deadlineLabel = new QLabel("截止: " + item.deadline().toString("yyyy-MM-dd"), this);

    int daysLeft = QDate::currentDate().daysTo(item.deadline());
    QString daysText = daysLeft >= 0 ? QString::number(daysLeft) + " 天" : "已过期";
    m_daysLeftLabel = new QLabel("剩余: " + daysText, this);
    m_daysLeftLabel->setStyleSheet(daysLeft < 3 ? "color: red;" : "color: green;");

    m_deleteButton = new QPushButton("删除", this);
    m_deleteButton->setStyleSheet("background-color: #ff6b6b; color: white; border: none; padding: 2px 5px;");
    m_deleteButton->setFixedWidth(50);
    connect(m_deleteButton, &QPushButton::clicked, this, &ddlWidget::onDeleteClicked);

    layout->addWidget(m_titleLabel);
    layout->addWidget(m_deadlineLabel);
    layout->addWidget(m_daysLeftLabel);
    layout->addWidget(m_deleteButton, 0, Qt::AlignRight);

    setLayout(layout);
}
ddlItem ddlWidget::getItem() const
{
    return m_item;
}
void ddlWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked(this);
    }
    QWidget::mousePressEvent(event);
}

void ddlWidget::onDeleteClicked()
{
    emit deleteRequested(this);
}
void ddlWidget::updateDisplay() {
    int daysLeft = QDate::currentDate().daysTo(m_item.deadline());
    QString daysText = daysLeft >= 0 ? QString::number(daysLeft) + " 天" : "已过期";
    m_daysLeftLabel->setText("剩余: " + daysText);
    m_daysLeftLabel->setStyleSheet(daysLeft < 3 ? "color: red;" : "color: green;");
}

QDate ddlWidget::deadline() const {
    return m_item.deadline();
}
