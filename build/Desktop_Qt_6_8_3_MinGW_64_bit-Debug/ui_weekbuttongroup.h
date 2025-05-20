/********************************************************************************
** Form generated from reading UI file 'weekbuttongroup.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WEEKBUTTONGROUP_H
#define UI_WEEKBUTTONGROUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WeekButtonGroup
{
public:

    void setupUi(QWidget *WeekButtonGroup)
    {
        if (WeekButtonGroup->objectName().isEmpty())
            WeekButtonGroup->setObjectName("WeekButtonGroup");
        WeekButtonGroup->resize(400, 300);

        retranslateUi(WeekButtonGroup);

        QMetaObject::connectSlotsByName(WeekButtonGroup);
    } // setupUi

    void retranslateUi(QWidget *WeekButtonGroup)
    {
        WeekButtonGroup->setWindowTitle(QCoreApplication::translate("WeekButtonGroup", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WeekButtonGroup: public Ui_WeekButtonGroup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WEEKBUTTONGROUP_H
