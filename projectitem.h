#ifndef PROJECTITEM_H
#define PROJECTITEM_H
#include <QString>
#include <QDate>
#include <QWidget>
#include <QJsonObject>
#include<QList>
class goalitem{
public:
    goalitem(const QString& title, const QDate& deadline,bool finish, const QString& description = "");
    QString title() const;
    QDate deadline() const;
    QString description() const;

    bool finish()const;
    void finishit();
    bool operator ==(const goalitem &other)const;

    QJsonObject toJson() const;
    static goalitem fromJson(const QJsonObject &json);

private:
    QString m_title;
    QDate m_deadline;
    QString m_description;
    bool iffinish;
};
class projectItem
{
public:
    projectItem(const QString& title, const QDate& deadline, const QList<goalitem> &goals = {},const QString& description = "",int totalnum=1,int finishednum=0);
    QString title() const;
    QDate deadline() const;
    QString description() const;
    QList<goalitem> goals()const;
    int total()const;
    int finished()const;

    bool iffinished() const;
    bool operator==(const projectItem &other) const;

    QJsonObject toJson() const;
    static projectItem fromJson(const QJsonObject &json);

private:
    QString m_title;
    QDate m_deadline;
    QString m_description;
    QList<goalitem> list;
    int totalnum ;
    int finishednum;
};
#endif // PROJECTITEM_H
