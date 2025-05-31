#include "longtermproject.h"
#include "ui_longtermproject.h"
#include "projectwidget.h"
#include "ddlreminder.h"
#include "mainwindow.h"
#include<QFIle>
#include <QJsonDocument>
#include <QJsonArray>
#include <QMessageBox>
#include <QDialog>
#include <QInputDialog>
#include <QFormLayout>
#include <QDateEdit>

LongTermProject::LongTermProject(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LongTermProject)
{
    ui->setupUi(this);
    QString m_saveFilePath = " longtermproject.json";
    m_scrollContent = new QWidget;
    m_layout = new QVBoxLayout(m_scrollContent);
    m_layout->setAlignment(Qt::AlignTop); // 防止内容集中在中间
    loadFromFile(m_saveFilePath);
    m_scrollContent->setLayout(m_layout);
    ui->scrollArea->setWidget(m_scrollContent); // 使用 Designer 中的 scrollArea
    ui->scrollArea->setWidgetResizable(true);
}
void LongTermProject::addProject(const projectItem &item) {
    m_projects.append(item);
    projectItemWidget *widget = new projectItemWidget(item, m_scrollContent);
    connect(widget, &projectItemWidget::deleteRequested, this, &LongTermProject::removeProject);
    m_layout->addWidget(widget);
}
void LongTermProject::setDDLReminder(ddlReminder *reminder) {
    ddl = reminder;
}
void LongTermProject::removeProject(projectItemWidget *widget) {
    projectItem item = widget->getItem();

    // 找到项目索引并删除
    int index = -1;
    for (int i = 0; i < m_projects.size(); ++i) {
        if (m_projects[i] == item) { // 确保projectItem重载了==，或用自定义比较
            index = i;
            break;
        }
    }
    if (index != -1) {
        m_projects.removeAt(index);
        qDebug()<<"delete"<<m_saveFilePath;
    }

    m_layout->removeWidget(widget);
    widget->deleteLater();

    saveToFile(m_saveFilePath);
    refreshDisplay();
    emit dataChanged();
}


void LongTermProject::saveToFile(const QString &filename) {
    QJsonArray array;
    for (const auto &p : m_projects)
        array.append(p.toJson());

    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument(array).toJson());
        file.close();
    }
}

void LongTermProject::loadFromFile(const QString &filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) return;

    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonArray array = doc.array();

    m_projects.clear();
    QLayoutItem *child;
    while ((child = m_layout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    for (const QJsonValue &v : array) {
        if (v.isObject()) {
            projectItem item = projectItem::fromJson(v.toObject());
            addProject(item);
        }
    }
}
LongTermProject::~LongTermProject()
{
    delete ui;
}
void LongTermProject::refreshDisplay()
{
    if (!m_scrollContent || !m_scrollContent->layout()) return;

    // 清空旧部件
    QLayoutItem *child;
    while ((child = m_scrollContent->layout()->takeAt(0)) != nullptr) {
        if (child->widget()) {
            child->widget()->deleteLater();
        }
        delete child;
    }

    // 重新添加所有项目部件
    for (const projectItem &item : m_projects) {
        projectItemWidget *widget = new projectItemWidget(item, m_scrollContent);
        connect(widget, &projectItemWidget::deleteRequested, this, &LongTermProject::removeProject);
        connect(widget, &projectItemWidget::dataChanged, this, &LongTermProject::dataChanged);
        m_scrollContent->layout()->addWidget(widget);
    }
}

void LongTermProject::on_pushButton_clicked()
{
    bool ok;

    // 输入项目标题
    QString projectTitle = QInputDialog::getText(this, "添加项目", "请输入项目标题:", QLineEdit::Normal, "", &ok);
    if (!ok || projectTitle.isEmpty()) return;

    // 输入项目描述
    QString projectDesc = QInputDialog::getText(this, "添加项目", "请输入项目描述（可选）:", QLineEdit::Normal, "", &ok);
    if (!ok) return;

    // 是否设置截止日期
    QMessageBox::StandardButton hasDeadline = QMessageBox::question(
        this, "是否设置截止日期", "你是否想为该项目设置截止日期？",
        QMessageBox::Yes | QMessageBox::No);

    QDate projectDeadline;
    int i=0;
    if (hasDeadline == QMessageBox::Yes) {
        QDialog deadlineDialog(this);
        QFormLayout deadlineForm(&deadlineDialog);
        i=1;
        QDateEdit *dateEdit = new QDateEdit(QDate::currentDate(), &deadlineDialog);
        dateEdit->setCalendarPopup(true);
        dateEdit->setMinimumDate(QDate::currentDate());
        deadlineForm.addRow("选择截止日期:", dateEdit);

        QDialogButtonBox deadlineButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &deadlineDialog);
        deadlineForm.addRow(&deadlineButtons);

        connect(&deadlineButtons, &QDialogButtonBox::accepted, &deadlineDialog, &QDialog::accept);
        connect(&deadlineButtons, &QDialogButtonBox::rejected, &deadlineDialog, &QDialog::reject);

        if (deadlineDialog.exec() != QDialog::Accepted) return;
        projectDeadline = dateEdit->date();
    }

    // 输入子任务数量
    int goalCount = QInputDialog::getInt(this, "子任务数量", "请输入该项目的子任务数量:", 1, 1, 100, 1, &ok);
    if (!ok) return;

    QList<goalitem> goals;
    for (int i = 0; i < goalCount; ++i) {
        QString goalTitle = QInputDialog::getText(this, QString("子任务 %1").arg(i + 1),
                                                  "请输入子任务标题:", QLineEdit::Normal, "", &ok);
        if (!ok || goalTitle.isEmpty()) return;

        QString goalDesc = QInputDialog::getText(this, QString("子任务 %1").arg(i + 1),
                                                 "请输入子任务描述（可选）:", QLineEdit::Normal, "", &ok);
        if (!ok) return;
        QDate goalDeadline;
        if (QMessageBox::question(this, "子任务截止日期",
                                  QString("是否为子任务 %1 设置截止日期？").arg(i + 1),
                                  QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
            QDialog dialog(this);
            QFormLayout form(&dialog);
            QDateEdit *dateEdit = new QDateEdit(QDate::currentDate(), &dialog);
            dateEdit->setCalendarPopup(true);
            dateEdit->setMinimumDate(QDate::currentDate());
            form.addRow("选择截止日期:", dateEdit);
            QDialogButtonBox buttons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
            form.addRow(&buttons);
            connect(&buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
            connect(&buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
            if (dialog.exec() != QDialog::Accepted) return;
            goalDeadline = dateEdit->date();
            QString title="project"+projectTitle+"-"+goalTitle;
            ddl->add(title,goalDeadline,goalDesc);
            ddl->saveToFile("ddl_reminder.json");
        }

        goals.append(goalitem(goalTitle, goalDeadline, false, goalDesc));

    }

    // 创建并添加项目
    projectItem newProject(projectTitle, projectDeadline, goals, projectDesc, goalCount);
    if(i)   {
        ddl->add(projectTitle,projectDeadline,projectDesc);
        ddl->saveToFile("ddl_reminder.json");
    }
    m_projects.append(newProject);
    refreshDisplay();
    saveToFile(m_saveFilePath);
    emit dataChanged();
}

