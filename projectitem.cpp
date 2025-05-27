#include "projectitem.h"
#include "qjsonarray.h"

goalitem::goalitem(const QString& title, const QDate& deadline,bool finish,const QString& description)
    : m_title(title), m_deadline(deadline), m_description(description) ,iffinish(finish){}

QString goalitem::title() const { return m_title; }
QDate goalitem::deadline() const { return m_deadline; }
QString goalitem::description() const { return m_description; }
bool goalitem::finish()const{return iffinish;}
void goalitem::finishit(){iffinish=true;}
bool goalitem::operator==(const goalitem &other) const{
     return m_title == other.m_title &&
                  m_deadline == other.m_deadline &&
                  m_description == other.m_description;
}
QJsonObject goalitem::toJson() const {
    QJsonObject obj;
    obj["title"] = m_title;
    obj["deadline"] = m_deadline.toString(Qt::ISODate);
    obj["description"] = m_description;
    obj["finished"] = iffinish;
    return obj;
}

goalitem goalitem::fromJson(const QJsonObject &json) {
    QString title = json["title"].toString();
    QDate deadline = QDate::fromString(json["deadline"].toString(), Qt::ISODate);
    QString description = json["description"].toString();
    bool iffinish = json["finished"].toBool();
    return goalitem(title, deadline,iffinish, description);
}

projectItem::projectItem(const QString& title, const QDate& deadline, const QList<goalitem> &goals,const QString& description,const int num,const int finished)
    : m_title(title), m_deadline(deadline),m_description(description), list(goals),totalnum(num),finishednum(finished){}

QString projectItem::title() const { return m_title; }
QDate projectItem::deadline() const { return m_deadline; }
QString projectItem::description() const { return m_description; }
QList<goalitem> projectItem::goals()const{return list;}
int projectItem::total()const{return totalnum;}
int projectItem::finished ()const{return finishednum;}
bool projectItem::iffinished()const{return finishednum==totalnum;}


bool projectItem::operator==(const projectItem &other) const {
    return m_title == other.m_title &&
           m_deadline == other.m_deadline &&
           m_description == other.m_description &&
           list == other.list; // 注意：这要求 goalitem 也重载了 ==
}

QJsonObject projectItem::toJson() const {
    QJsonObject obj;
    obj["title"] = m_title;
    obj["deadline"] = m_deadline.toString(Qt::ISODate);
    obj["description"] = m_description;
    obj["totalnum"] = totalnum;
    obj["finishednum"] = finishednum;
    QJsonArray goals;
    for (const auto& g : list)
        goals.append(g.toJson());
    obj["goals"] = goals;

    return obj;
}

projectItem projectItem::fromJson(const QJsonObject &json) {
    QString title = json["title"].toString();
    QDate deadline = QDate::fromString(json["deadline"].toString(), Qt::ISODate);
    QString description = json["description"].toString();
    QList<goalitem> list;
    QJsonArray goalsArray = json["goals"].toArray();

    for (const QJsonValue& value : goalsArray) {
        list.append(goalitem::fromJson(value.toObject()));
    }
    int totalnum=json["totalnum"].toInt();
    int finishednum=json["finishednum"].toInt();
    projectItem item(title, deadline, list,description,totalnum,finishednum);
    item.totalnum = json["totalnum"].toInt();
    item.finishednum = json["finishednum"].toInt();
    QJsonArray goals = json["goals"].toArray();

    for (const auto& g : goals)
        item.list.append(goalitem::fromJson(g.toObject()));
    return item;
}
