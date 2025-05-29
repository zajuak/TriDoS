#ifndef DAILYDATA_H
#define DAILYDATA_H
#include <QWidget>
#include <qdatetime.h>
#include <QJsonObject>
#include <QString>
class dailydata
{
public:
    dailydata(QString _Title="", QString _Detail="", \
                    QDateTime _Start=QDateTime::currentDateTime(), QDateTime _End=QDateTime::currentDateTime(),\
                        QString _Kind="Today", bool _Finished=false);
    QString title() const;
    QDateTime start() const;
    QDateTime end() const;
    QString detail() const;
    QString kind() const;
    bool finished() const;

    QJsonObject toJson() const;
    static dailydata fromJson(const QJsonObject &json);

private:
    QString Title;
    QDateTime Start;
    QDateTime End;
    QString Detail;
    QString Kind;
    bool Finished;
};

#endif // DAILYDATA_H
