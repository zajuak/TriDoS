#include "pomodorowidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
PomodoroWidget::PomodoroWidget(QWidget *parent) : QWidget(parent)
{
    // 默认值
    workDuration = 25;
    breakDuration = 5;

    remainingSeconds = workDuration * 60;
    isWorking = true;

    setupUI();
}
void PomodoroWidget::setTimeDisplay()
{
    int minutes = remainingSeconds / 60;
    int seconds = remainingSeconds % 60;
    timeLabel->setText(QString("%1:%2")
                           .arg(minutes, 2, 10, QLatin1Char('0'))
                           .arg(seconds, 2, 10, QLatin1Char('0')));
}

void PomodoroWidget::startPomodoro()
{
    if (timer->isActive()) {
        timer->stop();
        startButton->setText("开始");
    } else {
        timer->start();
        startButton->setText("暂停");
    }
}

void PomodoroWidget::resetTimer()
{
    timer->stop();
    if (isWorking) {
        remainingSeconds = 25 * 60;
    } else {
        remainingSeconds = 5 * 60;
    }
    setTimeDisplay();
    startButton->setText("开始");
}
void PomodoroWidget::setupUI()
{
    // 主界面布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // 时间显示
    timeLabel = new QLabel(this);
    timeLabel->setAlignment(Qt::AlignCenter);
    QFont font = timeLabel->font();
    font.setPointSize(24);
    timeLabel->setFont(font);
    setTimeDisplay();
    mainLayout->addWidget(timeLabel);

    // 按钮布局
    QHBoxLayout *buttonLayout = new QHBoxLayout();

    startButton = new QPushButton("开始", this);
    resetButton = new QPushButton("重置", this);
    settingsButton = new QPushButton("设置", this);

    buttonLayout->addWidget(startButton);
    buttonLayout->addWidget(resetButton);
    buttonLayout->addWidget(settingsButton);
    mainLayout->addLayout(buttonLayout);

    // 设置面板 (初始隐藏)
    settingsPanel = new QWidget(this);
    QFormLayout *formLayout = new QFormLayout(settingsPanel);

    workTimeSpin = new QSpinBox(this);
    workTimeSpin->setRange(1, 120);  // 1-120分钟
    workTimeSpin->setValue(workDuration);
    workTimeSpin->setSuffix(" 分钟");

    breakTimeSpin = new QSpinBox(this);
    breakTimeSpin->setRange(1, 30);  // 1-30分钟
    breakTimeSpin->setValue(breakDuration);
    breakTimeSpin->setSuffix(" 分钟");

    applyButton = new QPushButton("应用", this);

    formLayout->addRow("工作时间:", workTimeSpin);
    formLayout->addRow("休息时间:", breakTimeSpin);
    formLayout->addRow(applyButton);

    settingsPanel->setLayout(formLayout);
    settingsPanel->hide();
    mainLayout->addWidget(settingsPanel);

    // 定时器
    timer = new QTimer(this);
    timer->setInterval(1000); // 1秒

    // 连接信号槽
    connect(startButton, &QPushButton::clicked, this, &PomodoroWidget::startPomodoro);
    connect(resetButton, &QPushButton::clicked, this, &PomodoroWidget::resetTimer);
    connect(settingsButton, &QPushButton::clicked, [this]() {
        settingsPanel->setVisible(!settingsPanel->isVisible());
    });
    connect(applyButton, &QPushButton::clicked, this, &PomodoroWidget::applySettings);
    connect(timer, &QTimer::timeout, this, &PomodoroWidget::updateTime);
}

void PomodoroWidget::applySettings()
{
    workDuration = workTimeSpin->value();
    breakDuration = breakTimeSpin->value();

    if(isWorking) {
        remainingSeconds = workDuration * 60;
    } else {
        remainingSeconds = breakDuration * 60;
    }

    setTimeDisplay();
    settingsPanel->hide();
}

void PomodoroWidget::updateTime()
{
    remainingSeconds--;
    setTimeDisplay();

    if (remainingSeconds <= 0) {
        timer->stop();
        if (isWorking) {
            // 切换到休息时间
            remainingSeconds = breakDuration * 60;
            isWorking = false;
            timeLabel->setText("休息时间到!");
        } else {
            // 切换到工作时间
            remainingSeconds = workDuration * 60;
            isWorking = true;
            timeLabel->setText("工作时间到!");
        }
        QTimer::singleShot(2000, this, [this]() {
            setTimeDisplay();
            startButton->setText("开始");
        });
    }
}
