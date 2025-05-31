#ifndef LONGTERMPROJECT_H
#define LONGTERMPROJECT_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include<QList>
#include <QPushButton>
#include<QDate>
#include "projectitem.h"
#include "projectwidget.h"
#include "ddlreminder.h"

class QVBoxLayout;
class QScrollArea;

namespace Ui {
class LongTermProject;
class goalItemWidget;
class projectItemWidget;
}


class LongTermProject : public QWidget
{
    Q_OBJECT

public:
    explicit LongTermProject(QWidget *parent = nullptr);
    void setDDLReminder(ddlReminder *reminder);
    void addProject(const projectItem &item);
    void loadFromFile(const QString &filename);
    void saveToFile(const QString &filename);
    ~LongTermProject();
public slots:
    void refreshDisplay();

private slots:
    void on_pushButton_clicked();
    void removeProject(projectItemWidget *widget);
signals:
    void dataChanged();
private:
    Ui::LongTermProject *ui;
    QScrollArea *m_scrollArea;
    QWidget *m_scrollContent;
    QVBoxLayout *m_layout;
    QList<projectItem> m_projects;
    QString m_saveFilePath=" longtermproject.json";
    ddlReminder *ddl;
};

#endif // LONGTERMPROJECT_H
