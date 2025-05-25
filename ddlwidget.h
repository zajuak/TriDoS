#ifndef DDLWIDGET_H
#define DDLWIDGET_H
#include "ddlitem.h"
#include <QWidget>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include<QPushButton>
class ddlWidget:public QWidget
{
    Q_OBJECT
public:
    ddlWidget(const ddlItem&item,QWidget*parent=nullptr);
    void updateDisplay();
    QDate deadline()const;
    ddlItem getItem() const;

signals:
    void clicked(ddlWidget *widget);
    void deleteRequested(ddlWidget *widget);

protected:
    void mousePressEvent(QMouseEvent *event) override;

private slots:
    void onDeleteClicked();

private:
    ddlItem m_item;
    QLabel *m_titleLabel;
    QLabel *m_deadlineLabel;
    QLabel *m_daysLeftLabel;
    QPushButton *m_deleteButton;
};

#endif // DDLWIDGET_H
