#include "ddlreminder.h"
#include "ui_ddlreminder.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include <QTimer>
#include <algorithm>
#include <QInputDialog>
#include <QDateEdit>
#include <QDialog>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include<QMessageBox>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDir>
ddlReminder::ddlReminder(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ddlReminder)
{
    ui->setupUi(this);
    setupScrollArea();
    loadFromFile(m_saveFilePath);
    m_expiryTimer = new QTimer(this);
    connect(m_expiryTimer, &QTimer::timeout, this, &ddlReminder::removeExpiredDDLs);
    m_expiryTimer->start(3600000); // 每小时检查一次
    connect(ui->pushButton, &QPushButton::clicked, this, &ddlReminder::on_pushButton_clicked);
    QTimer *autoSaveTimer = new QTimer(this);
    connect(autoSaveTimer, &QTimer::timeout, this, &ddlReminder::autoSave);
    autoSaveTimer->start(5 * 60 * 1000);  // 5分钟
}

ddlReminder::~ddlReminder()
{
    delete ui;
}
void ddlReminder::autoSave()
{
    saveToFile(m_saveFilePath);
}
void ddlReminder::setupScrollArea()
{
    // 设置滚动区域
    m_scrollContent = new QWidget();
    QVBoxLayout *contentLayout = new QVBoxLayout(m_scrollContent);
    contentLayout->setAlignment(Qt::AlignTop);
    contentLayout->setSpacing(10);

    ui->scrollArea->setWidget(m_scrollContent);
    ui->scrollArea->setWidgetResizable(true);
}
void ddlReminder::add(const QString &title, const QDate &deadline, const QString &description)
{
    m_ddlItems.append(ddlItem(title, deadline, description));
    sortDDLs();
    refreshDisplay();
    saveToFile(m_saveFilePath);
    emit dataChanged();
}
void ddlReminder::saveToFile(const QString &filename)
{
    QJsonArray jsonArray;
    for (const ddlItem &item : m_ddlItems) {
        jsonArray.append(item.toJson());
    }

    QJsonDocument doc(jsonArray);
    QFile file(filename);

    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "无法打开文件用于写入:" << filename;
        return;
    }

    file.write(doc.toJson());
    file.close();

    qDebug() << "DDL数据已保存到:" << filename;
    emit dataChanged();
}

void ddlReminder::loadFromFile(const QString &filename)
{
    QFile file(filename);
    if (!file.exists()) {
        qDebug() << "保存文件不存在，将创建新文件";
        return;
    }

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "无法打开文件用于读取:" << filename;
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isNull() || !doc.isArray()) {
        qWarning() << "文件格式无效:" << filename;
        return;
    }

    m_ddlItems.clear();
    QJsonArray jsonArray = doc.array();
    for (const QJsonValue &value : jsonArray) {
        if (value.isObject()) {
            ddlItem item = ddlItem::fromJson(value.toObject());
            if (!item.title().isEmpty()) {  // 跳过无效条目
                m_ddlItems.append(item);
            }
        }
    }

    sortDDLs();
    refreshDisplay();

    qDebug() << "从文件加载了" << m_ddlItems.size() << "个DDL事项";
    emit dataChanged();
}
void ddlReminder::clearAll()
{
    m_ddlItems.clear();
    refreshDisplay();
    emit dataChanged();
}
int ddlReminder::count() const
{
    return m_ddlItems.size();
}
void ddlReminder::refreshDisplay()
{
    QLayoutItem *child;
    while ((child = m_scrollContent->layout()->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    for (const ddlItem &item : m_ddlItems) {
        ddlWidget *widget = new ddlWidget(item, m_scrollContent);
        connect(widget, &ddlWidget::clicked, this, &ddlReminder::onDDLClicked);
        connect(widget, &ddlWidget::deleteRequested, this, &ddlReminder::onDeleteDDL);
        m_scrollContent->layout()->addWidget(widget);
    }
    saveToFile(m_saveFilePath);
}
void ddlReminder::sortDDLs()
{
    std::sort(m_ddlItems.begin(), m_ddlItems.end(), [](const ddlItem &a, const ddlItem &b) {
        return a.deadline() < b.deadline();
    });
}
void ddlReminder::removeExpiredDDLs()
{
    bool changed = false;
    for (int i = m_ddlItems.size()-1; i >= 0; --i) {
        if (m_ddlItems[i].isExpired()) {
            m_ddlItems.removeAt(i);
            changed = true;
        }
    }

    if (changed) {
        refreshDisplay();
        emit dataChanged();
    }
}
void ddlReminder::on_pushButton_clicked()
{
    bool ok;
    QString title = QInputDialog::getText(this, "添加DDL", "请输入事项标题:", QLineEdit::Normal, "", &ok);
    if (!ok || title.isEmpty()) return;

    // 创建日期选择对话框
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

    // 获取描述(可选)
    QString description = QInputDialog::getText(this, "添加DDL", "描述(可选):", QLineEdit::Normal, "", &ok);

    // 添加DDL
    add(title, dateEdit->date(), description);
}
void ddlReminder::onDDLClicked(ddlWidget *widget)
{
    showDescriptionDialog(widget->getItem().title(), widget->getItem().description());
}

void ddlReminder::onDeleteDDL(ddlWidget *widget)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "确认删除",
                                  "确定要删除 '" + widget->getItem().title() + "' 吗?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        // 修改为使用索引删除，避免依赖operator==
        for (int i = 0; i < m_ddlItems.size(); ++i) {
            if (m_ddlItems[i].title() == widget->getItem().title() &&
                m_ddlItems[i].deadline() == widget->getItem().deadline()) {
                m_ddlItems.removeAt(i);
                break;
            }
        }
        refreshDisplay();
        saveToFile(m_saveFilePath);
    }
}
void ddlReminder::showDescriptionDialog(const QString &title, const QString &description)
{
    QDialog dialog(this);
    dialog.setWindowTitle(title);

    QVBoxLayout *layout = new QVBoxLayout(&dialog);

    QLabel *descLabel = new QLabel(description.isEmpty() ? "无描述" : description, &dialog);
    descLabel->setWordWrap(true);
    descLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok, &dialog);

    layout->addWidget(descLabel);
    layout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);

    dialog.exec();
}

