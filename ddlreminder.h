#ifndef DDLREMINDER_H
#define DDLREMINDER_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include<QList>
#include<QDate>
#include "ddlitem.h"
#include"ddlwidget.h"

class QVBoxLayout;
class QScrollArea;
class ddlWidget;

namespace Ui {
class ddlReminder;
}

class ddlReminder : public QWidget
{
    Q_OBJECT

public:
    explicit ddlReminder(QWidget *parent = nullptr);
    void clearAll();
    int count()const;
    void saveToFile(const QString &filename);
    void loadFromFile(const QString &filename);
    void add(const QString&title,const QDate&deadline,const QString&description="");
    ~ddlReminder();
    const QList<ddlItem>& getAllItems() const { return m_ddlItems; }

public slots:
    void refreshDisplay();
private slots:
    void on_pushButton_clicked();

    void removeExpiredDDLs();
    void onDDLClicked(ddlWidget *widget);
    void onDeleteDDL(ddlWidget *widget);
    void autoSave();
signals:
    void dataChanged();
private:
    Ui::ddlReminder *ui;
    void sortDDLs();
    void setupScrollArea();
    void showDescriptionDialog(const QString &title, const QString &description);
    QList<ddlItem> m_ddlItems;
    QScrollArea *m_scrollArea;
    QWidget *m_scrollContent;
    QVBoxLayout *m_mainLayout;
    QTimer *m_expiryTimer;
    QString m_saveFilePath = "ddl_reminder.json";

};

#endif // DDLREMINDER_H
