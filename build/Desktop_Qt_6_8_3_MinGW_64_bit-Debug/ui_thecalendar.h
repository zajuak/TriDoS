/********************************************************************************
** Form generated from reading UI file 'thecalendar.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_THECALENDAR_H
#define UI_THECALENDAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TheCalendar
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_2;
    QPushButton *dailySentence;
    QHBoxLayout *horizontalLayout;
    QPushButton *Monday;
    QPushButton *Tuesday;
    QPushButton *Wednesday;
    QPushButton *Thursday;
    QPushButton *Friday;
    QPushButton *Saturday;
    QPushButton *Sunday;
    QLabel *label;

    void setupUi(QWidget *TheCalendar)
    {
        if (TheCalendar->objectName().isEmpty())
            TheCalendar->setObjectName("TheCalendar");
        TheCalendar->resize(598, 192);
        TheCalendar->setMinimumSize(QSize(0, 192));
        TheCalendar->setMaximumSize(QSize(16777215, 385));
        verticalLayout_2 = new QVBoxLayout(TheCalendar);
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        pushButton_2 = new QPushButton(TheCalendar);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setMinimumSize(QSize(256, 24));
        pushButton_2->setMaximumSize(QSize(256, 32));

        horizontalLayout_2->addWidget(pushButton_2);

        dailySentence = new QPushButton(TheCalendar);
        dailySentence->setObjectName("dailySentence");
        dailySentence->setMinimumSize(QSize(256, 24));
        dailySentence->setMaximumSize(QSize(256, 32));

        horizontalLayout_2->addWidget(dailySentence);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        Monday = new QPushButton(TheCalendar);
        Monday->setObjectName("Monday");
        Monday->setMinimumSize(QSize(0, 64));
        Monday->setMaximumSize(QSize(108, 16777215));

        horizontalLayout->addWidget(Monday);

        Tuesday = new QPushButton(TheCalendar);
        Tuesday->setObjectName("Tuesday");
        Tuesday->setMinimumSize(QSize(0, 64));
        Tuesday->setMaximumSize(QSize(108, 16777215));

        horizontalLayout->addWidget(Tuesday);

        Wednesday = new QPushButton(TheCalendar);
        Wednesday->setObjectName("Wednesday");
        Wednesday->setMinimumSize(QSize(0, 64));
        Wednesday->setMaximumSize(QSize(108, 16777215));

        horizontalLayout->addWidget(Wednesday);

        Thursday = new QPushButton(TheCalendar);
        Thursday->setObjectName("Thursday");
        Thursday->setMinimumSize(QSize(0, 64));
        Thursday->setMaximumSize(QSize(108, 16777215));

        horizontalLayout->addWidget(Thursday);

        Friday = new QPushButton(TheCalendar);
        Friday->setObjectName("Friday");
        Friday->setMinimumSize(QSize(0, 64));
        Friday->setMaximumSize(QSize(108, 16777215));

        horizontalLayout->addWidget(Friday);

        Saturday = new QPushButton(TheCalendar);
        Saturday->setObjectName("Saturday");
        Saturday->setMinimumSize(QSize(0, 64));
        Saturday->setMaximumSize(QSize(108, 16777215));

        horizontalLayout->addWidget(Saturday);

        Sunday = new QPushButton(TheCalendar);
        Sunday->setObjectName("Sunday");
        Sunday->setMinimumSize(QSize(0, 64));
        Sunday->setMaximumSize(QSize(108, 16777215));

        horizontalLayout->addWidget(Sunday);


        verticalLayout_2->addLayout(horizontalLayout);

        label = new QLabel(TheCalendar);
        label->setObjectName("label");
        label->setMinimumSize(QSize(0, 48));
        label->setMaximumSize(QSize(16777215, 48));

        verticalLayout_2->addWidget(label);


        retranslateUi(TheCalendar);

        QMetaObject::connectSlotsByName(TheCalendar);
    } // setupUi

    void retranslateUi(QWidget *TheCalendar)
    {
        TheCalendar->setWindowTitle(QCoreApplication::translate("TheCalendar", "Form", nullptr));
        pushButton_2->setText(QCoreApplication::translate("TheCalendar", "\346\237\245\347\234\213\346\210\221\347\232\204\346\227\245\345\216\206", nullptr));
        dailySentence->setText(QCoreApplication::translate("TheCalendar", "\346\237\245\347\234\213\346\257\217\346\227\245\344\270\200\345\217\245", nullptr));
        Monday->setText(QCoreApplication::translate("TheCalendar", "\345\221\250\344\270\200", nullptr));
        Tuesday->setText(QCoreApplication::translate("TheCalendar", "\345\221\250\344\272\214", nullptr));
        Wednesday->setText(QCoreApplication::translate("TheCalendar", "\345\221\250\344\270\211", nullptr));
        Thursday->setText(QCoreApplication::translate("TheCalendar", "\345\221\250\345\233\233", nullptr));
        Friday->setText(QCoreApplication::translate("TheCalendar", "\345\221\250\344\272\224", nullptr));
        Saturday->setText(QCoreApplication::translate("TheCalendar", "\345\221\250\345\205\255", nullptr));
        Sunday->setText(QCoreApplication::translate("TheCalendar", "\345\221\250\346\227\245", nullptr));
        label->setText(QCoreApplication::translate("TheCalendar", "<html><head/><body><p><span style=\" font-size:20pt; font-weight:700;\">\345\275\223\345\211\215\351\230\266\346\256\265\347\212\266\346\200\201\357\274\232</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TheCalendar: public Ui_TheCalendar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_THECALENDAR_H
