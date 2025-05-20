/********************************************************************************
** Form generated from reading UI file 'ddlreminder.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DDLREMINDER_H
#define UI_DDLREMINDER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ddlReminder
{
public:
    QLabel *label;
    QPushButton *pushButton;

    void setupUi(QWidget *ddlReminder)
    {
        if (ddlReminder->objectName().isEmpty())
            ddlReminder->setObjectName("ddlReminder");
        ddlReminder->resize(400, 300);
        label = new QLabel(ddlReminder);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 20, 101, 24));
        label->setMinimumSize(QSize(64, 24));
        pushButton = new QPushButton(ddlReminder);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(170, 10, 56, 32));
        pushButton->setMinimumSize(QSize(32, 32));

        retranslateUi(ddlReminder);

        QMetaObject::connectSlotsByName(ddlReminder);
    } // setupUi

    void retranslateUi(QWidget *ddlReminder)
    {
        ddlReminder->setWindowTitle(QCoreApplication::translate("ddlReminder", "Form", nullptr));
        label->setText(QCoreApplication::translate("ddlReminder", "<html><head/><body><p><span style=\" font-size:16pt; font-weight:700;\">Deadline:</span></p></body></html>", nullptr));
        pushButton->setText(QCoreApplication::translate("ddlReminder", "\350\256\276\347\275\256ddl", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ddlReminder: public Ui_ddlReminder {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DDLREMINDER_H
