/********************************************************************************
** Form generated from reading UI file 'longtermproject.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LONGTERMPROJECT_H
#define UI_LONGTERMPROJECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LongTermProject
{
public:
    QLabel *label;
    QPushButton *pushButton;

    void setupUi(QWidget *LongTermProject)
    {
        if (LongTermProject->objectName().isEmpty())
            LongTermProject->setObjectName("LongTermProject");
        LongTermProject->resize(400, 300);
        label = new QLabel(LongTermProject);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 96, 41));
        label->setMinimumSize(QSize(96, 36));
        pushButton = new QPushButton(LongTermProject);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(170, 10, 56, 32));
        pushButton->setMinimumSize(QSize(32, 32));

        retranslateUi(LongTermProject);

        QMetaObject::connectSlotsByName(LongTermProject);
    } // setupUi

    void retranslateUi(QWidget *LongTermProject)
    {
        LongTermProject->setWindowTitle(QCoreApplication::translate("LongTermProject", "Form", nullptr));
        label->setText(QCoreApplication::translate("LongTermProject", "<html><head/><body><p><span style=\" font-size:16pt; font-weight:700;\">\346\210\221\347\232\204\351\241\271\347\233\256\357\274\232</span></p></body></html>", nullptr));
        pushButton->setText(QCoreApplication::translate("LongTermProject", "\346\267\273\345\212\240\351\241\271\347\233\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LongTermProject: public Ui_LongTermProject {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LONGTERMPROJECT_H
