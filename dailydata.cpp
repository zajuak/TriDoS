#include "dailydata.h"
#include <QWidget>
#include <qdatetime.h>
dailydata::dailydata(QString _Title, QString _Detail, QDateTime _Start, QDateTime _End, QString _Kind, bool _Finished):
    Title(_Title)
    ,Start(_Start)
    ,End(_End)
    ,Detail(_Detail)
    ,Kind(_Kind)
    ,Finished(_Finished)
{

}
QString dailydata::title() const {
    return Title;
}
QDateTime dailydata::start() const{
    return Start;
}
QDateTime dailydata::end() const{
    return End;
}
QString dailydata::detail() const{
    return Detail;
}
QString dailydata::kind() const{
    return Kind;
}
bool dailydata::finished() const{
    return Finished;
}

QJsonObject dailydata::toJson() const{
    QJsonObject json;
    json["title"] = Title;
    json["Start"] = Start.toString("yyyy-MM-dd");
    json["End"] = End.toString("yyyy-MM-dd");
    json["Detail"] = Detail;
    json["Kind"] = Kind;
    json["Finished"] = Finished;
    return json;
}
dailydata dailydata::fromJson(const QJsonObject &json){
    QString title = json["title"].toString();
    QString detail = json["Detail"].toString();
    QDateTime start  = QDateTime::fromString(json["Start"].toString(), "yyyy-MM-dd");
    QDateTime end  = QDateTime::fromString(json["End"].toString(), "yyyy-MM-dd");
    QString kind = json["Kind"].toString();
    bool finished = json["Finished"].toBool();
    return dailydata(title, detail, start, end, kind, finished);
}
