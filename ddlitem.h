#ifndef DDLITEM_H
#define DDLITEM_H
#include <QString>
#include <QDate>
#include <QWidget>
#include <QJsonObject>
class ddlItem
{
public:
    ddlItem(const QString& title, const QDate& deadline, const QString& description = "");
    QString title() const;
    QDate deadline() const;
    QString description() const;

    bool isExpired() const;
    bool operator==(const ddlItem &other) const;

    QJsonObject toJson() const;
    static ddlItem fromJson(const QJsonObject &json);

private:
    QString m_title;
    QDate m_deadline;
    QString m_description;
};

#endif // DDLITEM_H
