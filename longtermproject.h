#ifndef LONGTERMPROJECT_H
#define LONGTERMPROJECT_H

#include <QWidget>

namespace Ui {
class LongTermProject;
}

class LongTermProject : public QWidget
{
    Q_OBJECT

public:
    explicit LongTermProject(QWidget *parent = nullptr);
    ~LongTermProject();

private:
    Ui::LongTermProject *ui;
};

#endif // LONGTERMPROJECT_H
