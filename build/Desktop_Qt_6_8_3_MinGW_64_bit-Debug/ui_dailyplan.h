/********************************************************************************
** Form generated from reading UI file 'dailyplan.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DAILYPLAN_H
#define UI_DAILYPLAN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DailyPlan
{
public:
    QLabel *label;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pomodroButton;
    QLabel *label_2;

    void setupUi(QWidget *DailyPlan)
    {
        if (DailyPlan->objectName().isEmpty())
            DailyPlan->setObjectName("DailyPlan");
        DailyPlan->resize(587, 490);
        label = new QLabel(DailyPlan);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 0, 192, 64));
        label->setMinimumSize(QSize(192, 64));
        label->setMaximumSize(QSize(16777215, 64));
        horizontalLayoutWidget = new QWidget(DailyPlan);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(160, 10, 160, 41));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(horizontalLayoutWidget);
        pushButton->setObjectName("pushButton");
        pushButton->setMinimumSize(QSize(32, 32));

        horizontalLayout->addWidget(pushButton);

        pomodroButton = new QPushButton(horizontalLayoutWidget);
        pomodroButton->setObjectName("pomodroButton");
        pomodroButton->setMinimumSize(QSize(32, 32));

        horizontalLayout->addWidget(pomodroButton);

        label_2 = new QLabel(DailyPlan);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 440, 96, 32));
        label_2->setMinimumSize(QSize(96, 32));

        retranslateUi(DailyPlan);

        QMetaObject::connectSlotsByName(DailyPlan);
    } // setupUi

    void retranslateUi(QWidget *DailyPlan)
    {
        DailyPlan->setWindowTitle(QCoreApplication::translate("DailyPlan", "Form", nullptr));
        label->setText(QCoreApplication::translate("DailyPlan", "<html><head/><body><p><span style=\" font-size:24pt; font-weight:700;\">\346\257\217\346\227\245\350\256\241\345\210\222\357\274\232</span></p></body></html>", nullptr));
        pushButton->setText(QCoreApplication::translate("DailyPlan", "\346\267\273\345\212\240\344\272\213\351\241\271", nullptr));
        pomodroButton->setText(QCoreApplication::translate("DailyPlan", "\347\225\252\350\214\204\351\222\237", nullptr));
        label_2->setText(QCoreApplication::translate("DailyPlan", "<html><head/><body><p><span style=\" font-size:16pt; font-weight:700;\">\344\271\240\346\203\257\346\211\223\345\215\241\357\274\232</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DailyPlan: public Ui_DailyPlan {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DAILYPLAN_H
