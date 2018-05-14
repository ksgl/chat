#include "friend.h"

using namespace chat::data;

namespace chat {
namespace models {

std::map<int, QString> Friend::statusMapper = std::map<int, QString> {
    { Friend::eStatus::Unknown, "" },
    { Friend::eStatus::Online, "Online"},
    { Friend::eStatus::Offline, "Offline"}
};

Friend::Friend(QObject *parent)
    : Entity(parent, "friend")
{
    reference = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "reference", "User Ref")));
    status = static_cast<EnumeratorDecorator*>(addDataItem(new EnumeratorDecorator(this, "status", "Status", 0, statusMapper)));
    friendName = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "friendName" ,"Friend Name")));
    friendIp = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "friendIp", "Friend Ip")));
    lastVisit = static_cast<DateTimeDecorator*>(addDataItem(new DateTimeDecorator(this, "lastVisit", "Last Visit")));

    setPrimaryKey(reference);
}

Friend::Friend(QObject *parent, const QJsonObject &json)
    : Friend(parent)
{
    update(json);
}

void Friend::changeLastVisit(QDateTime newLastVisit)
{
    this->lastVisit->setValue(newLastVisit);
    emit lastVisitChanged();
}

void Friend::changeStatus(eStatus newStatus)
{
    this->status->setValue(newStatus);
    emit statusChanged();
}

void Friend::changeStatus(QString newStatus)
{
    for (auto pair : statusMapper) {
        if (pair.second == newStatus) {
            this->status->setValue(pair.first);
            emit statusChanged();
            break;
        }
    }
}

}
}

