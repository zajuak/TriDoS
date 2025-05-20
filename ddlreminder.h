#ifndef DDLREMINDER_H
#define DDLREMINDER_H

#include <QWidget>

namespace Ui {
class ddlReminder;
}

class ddlReminder : public QWidget
{
    Q_OBJECT

public:
    explicit ddlReminder(QWidget *parent = nullptr);
    ~ddlReminder();

private:
    Ui::ddlReminder *ui;
};

#endif // DDLREMINDER_H
