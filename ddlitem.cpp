    #include "ddlitem.h"

ddlItem::ddlItem (const QString& title, const QDate& deadline, const QString& description)
    : m_title(title), m_deadline(deadline), m_description(description)  {}

QString ddlItem::title()const{return m_title; }
QDate ddlItem::deadline()const {return m_deadline;}
QString ddlItem::description()const{return m_description;}
bool ddlItem::isExpired()const{
    return QDate::currentDate()>m_deadline;
}
bool ddlItem::operator==(const ddlItem &other) const {
    return m_title == other.m_title &&
           m_deadline == other.m_deadline &&
           m_description == other.m_description;
}
QJsonObject ddlItem::toJson() const
{
    QJsonObject json;
    json["title"] = m_title;
    json["deadline"] = m_deadline.toString(Qt::ISODate);
    json["description"] = m_description;
    return json;
}

ddlItem ddlItem::fromJson(const QJsonObject &json)
{
    QString title = json["title"].toString();
    QDate deadline = QDate::fromString(json["deadline"].toString(), Qt::ISODate);
    QString description = json["description"].toString();
    return ddlItem(title, deadline, description);
}
