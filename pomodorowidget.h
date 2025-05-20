#ifndef POMODOROWIDGET_H
#define POMODOROWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QSpinBox>
#include <QFormLayout>

class PomodoroWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PomodoroWidget(QWidget *parent = nullptr);

public slots:
    void applySettings();

private slots:
    void startPomodoro();
    void updateTime();
    void resetTimer();

private:
    void setupUI();
    void setTimeDisplay();

    // 控件
    QLabel *timeLabel;
    QPushButton *startButton;
    QPushButton *resetButton;
    QPushButton *settingsButton;
    QPushButton *applyButton;

    // 设置控件
    QSpinBox *workTimeSpin;
    QSpinBox *breakTimeSpin;
    QWidget *settingsPanel;

    QTimer *timer;
    int remainingSeconds;
    bool isWorking;

    // 配置值
    int workDuration;  // 工作时间(分钟)
    int breakDuration; // 休息时间(分钟)
};




#endif // POMODOROWIDGET_H
