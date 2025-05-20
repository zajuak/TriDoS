#include "dailysentencedialog.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

DailySentenceDialog::DailySentenceDialog(const QString &sentence, QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("每日一句");
    setFixedSize(300, 200);

    QLabel *label = new QLabel(sentence, this);
    label->setAlignment(Qt::AlignCenter);
    label->setWordWrap(true);
    label->setStyleSheet("font-size: 16px;");

    QPushButton *closeBtn = new QPushButton("关闭", this);
    connect(closeBtn, &QPushButton::clicked, this, &QDialog::accept);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(label);
    layout->addWidget(closeBtn, 0, Qt::AlignHCenter);
}
