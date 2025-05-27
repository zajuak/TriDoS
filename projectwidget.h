#ifndef PROJECTWIDGET_H
#define PROJECTWIDGET_H

#include "projectitem.h"
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFrame>
#include <QToolButton>
#include <QCheckBox>


class goalItemWidget : public QWidget {
    Q_OBJECT
public:
    goalItemWidget(const goalitem& item, QWidget* parent = nullptr);

    goalitem getGoalItem() const;
    void setGoalItem(const goalitem& item);

signals:
    void statusChanged();

private slots:
    void onCheckboxToggled(bool checked);

private:
    goalitem m_item;
    QLabel* m_titleLabel;
    QLabel* m_descLabel;
    QLabel* m_deadlineLabel;
    QCheckBox* m_checkbox;
};

class projectItemWidget : public QWidget {
    Q_OBJECT
public:
    projectItemWidget(const projectItem& item, QWidget* parent = nullptr);
    projectItem getItem() const;

signals:
    void deleteRequested(projectItemWidget* widget);
    void dataChanged();

private slots:
    void toggleGoals();
    void deleteProject();

private:
    projectItem m_item;
    QWidget* m_goalListWidget;
    QVBoxLayout* m_goalListLayout;
    QToolButton* m_toggleButton;
    bool m_expanded;
};
#endif // PROJECTWIDGET_H
