#ifndef DAILYSENTENCEDIALOG_H
#define DAILYSENTENCEDIALOG_H
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

class DailySentenceDialog : public QDialog
{
    Q_OBJECT  // 必须包含，用于信号槽机制

public:
    // 构造函数声明
    explicit DailySentenceDialog(const QString &sentence, QWidget *parent = nullptr);

private:
    // 成员变量声明
    QLabel *m_label;
    QPushButton *m_closeBtn;
};

#endif // DAILYSENTENCEDIALOG_H
