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

    reference->setValue(this->id());
    setPrimaryKey(reference);
}

Friend::Friend(QObject *parent, const Friend* other)
    : Friend(parent)
{
    QString newReference = other->reference->value();
    QString newFriendName = other->friendName->value();
    QString newFriendIp = other->friendIp->value();
    QDateTime newLasrVisit = other->lastVisit->value();

    if (!newReference.isEmpty())
    {
        this->reference->setValue(newReference);
    }
    this->status->setValue(other->status->value());
    this->friendName->setValue(newFriendName);
    this->friendIp->setValue(newFriendIp);
    this->lastVisit->setValue(newLasrVisit);
}

Friend::Friend(QObject *parent,
               const QString& newReference,
               const QString& newFriendName,
               const QString& newFriendIp,
               Friend::eStatus newStatus,
               const QDateTime& newLastVisit)
    : Friend(parent)
{
    if (!newReference.isEmpty())
    {
        this->reference->setValue(newReference);
    }
    this->status->setValue(newStatus);
    this->friendName->setValue(newFriendName);
    this->friendIp->setValue(newFriendIp);
    this->lastVisit->setValue(newLastVisit);
}

Friend::Friend(QObject *parent, const QJsonObject &json)
    : Friend(parent)
{
    update(json);
}

}
}

