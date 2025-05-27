#include "projectwidget.h"

goalItemWidget::goalItemWidget(const goalitem& item, QWidget* parent)
    : QWidget(parent), m_item(item)
{
    QVBoxLayout* layout = new QVBoxLayout(this);

    m_checkbox = new QCheckBox(item.title(), this);
    m_checkbox->setChecked(item.finish());
    connect(m_checkbox, &QCheckBox::toggled, this, &goalItemWidget::onCheckboxToggled);

    m_descLabel = new QLabel("描述：" + item.description(), this);
    m_deadlineLabel = new QLabel("截止日期：" + (item.deadline().isValid() ? item.deadline().toString("yyyy-MM-dd") : "无"), this);

    layout->addWidget(m_checkbox);
    layout->addWidget(m_descLabel);
    layout->addWidget(m_deadlineLabel);
    setLayout(layout);
}

goalitem goalItemWidget::getGoalItem() const {
    return m_item;
}

void goalItemWidget::setGoalItem(const goalitem& item) {
    m_item = item;
    m_checkbox->setText(item.title());
    m_checkbox->setChecked(item.finish());
    m_descLabel->setText("描述：" + item.description());
    m_deadlineLabel->setText("截止日期：" + (item.deadline().isValid() ? item.deadline().toString("yyyy-MM-dd") : "无"));
}

void goalItemWidget::onCheckboxToggled(bool checked) {
    m_item.finishit();
    emit statusChanged();
}


projectItemWidget::projectItemWidget(const projectItem& item, QWidget* parent)
    : QWidget(parent), m_item(item), m_expanded(false)
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QLabel* titleLabel = new QLabel("项目：" + m_item.title(), this);
    QLabel* descLabel = new QLabel("描述：" + m_item.description(), this);
    QLabel* deadlineLabel = new QLabel("截止日期：" + (m_item.deadline().isValid() ? m_item.deadline().toString("yyyy-MM-dd") : "无"), this);

    m_toggleButton = new QToolButton(this);
    m_toggleButton->setText("展开子任务");
    connect(m_toggleButton, &QToolButton::clicked, this, &projectItemWidget::toggleGoals);

    QPushButton* deleteBtn = new QPushButton("删除项目", this);
    connect(deleteBtn, &QPushButton::clicked, this, &projectItemWidget::deleteProject);

    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(descLabel);
    mainLayout->addWidget(deadlineLabel);
    mainLayout->addWidget(m_toggleButton);
    mainLayout->addWidget(deleteBtn);

    // 子任务列表
    m_goalListWidget = new QWidget(this);
    m_goalListLayout = new QVBoxLayout(m_goalListWidget);
    m_goalListWidget->setLayout(m_goalListLayout);
    m_goalListWidget->hide(); // 初始折叠

    for (const auto& goal : m_item.goals()) {
        goalItemWidget* widget = new goalItemWidget(goal, m_goalListWidget);
        connect(widget, &goalItemWidget::statusChanged, this, &projectItemWidget::dataChanged);
        m_goalListLayout->addWidget(widget);
    }

    mainLayout->addWidget(m_goalListWidget);
    setLayout(mainLayout);
}

projectItem projectItemWidget::getItem() const {
    return m_item;
}

void projectItemWidget::toggleGoals() {
    m_expanded = !m_expanded;
    m_goalListWidget->setVisible(m_expanded);
    m_toggleButton->setText(m_expanded ? "收起子任务" : "展开子任务");
}

void projectItemWidget::deleteProject() {
    emit deleteRequested(this);
}
