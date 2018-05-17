#include "friend-controller.h"

#include <QList>
#include <QDebug>

using namespace chat::models;

namespace chat {
namespace controllers {

class FriendController::Implementation
{
public:
    Implementation(FriendController* _friendController, UserModel* _user)
        : friendController(_friendController),
          user(_user)
    {
    }
    FriendController* friendController{nullptr};
    UserModel* user{nullptr};
};

FriendController::FriendController(QObject* parent, UserModel* _user)
    : QObject(parent)
{
    implementation.reset(new Implementation(this, _user));
}

FriendController::~FriendController()
{
}

void FriendController::addFriend(const chat::models::Friend* _friend)
{
    if (_friend != nullptr)
    {
        QObject* parent = implementation->user;
        implementation->user->friends->addEntity((new Friend(parent, _friend)));

        emit friendAdded();
    }
}

void FriendController::addFriend(const QString& _reference, const QString& _friendName, const QString& _friendIp,
                                 const models::Friend::eStatus _status, const QDateTime& _lastVisit)
{
    QObject* parent = implementation->user;
    Friend* newFriend = new Friend(parent, _reference, _friendName, _friendIp, _status, _lastVisit);
    implementation->user->friends->addEntity(newFriend);

    emit friendAdded();
}

models::Friend* FriendController::getFriend(const QString& friendReference) const
{
    QList<Friend*> friends = implementation->user->friends->derivedEntities();
    for (auto _friend : friends)
    {
        if (_friend->reference->value() == friendReference)
        {
            return _friend;
        }
    }
    return nullptr;
}

models::Friend* FriendController::getFriendByName(const QString& friendName) const
{
    QList<Friend*> friends = implementation->user->friends->derivedEntities();
    for (auto _friend : friends)
    {
        if (_friend->friendName->value() == friendName)
        {
            return _friend;
        }
    }
    return nullptr;
}

models::Friend::eStatus FriendController::getFriendStatus(const QString& friendReference) const
{
    Friend* _friend = getFriend(friendReference);
    if (_friend != nullptr)
    {
        return static_cast<models::Friend::eStatus>(_friend->status->value());
    }
    return Friend::eStatus::Unknown;
}

QList<models::Friend*>& FriendController::getFriendList() const
{
    return implementation->user->friends->derivedEntities();
}

QList<models::Friend*>* FriendController::getFriendListByStatus(const models::Friend::eStatus _status) const
{
    QList<Friend*> friends = implementation->user->friends->derivedEntities();
    QList<Friend*>* friendsWithStatus = new QList<Friend*>;
    for (auto _friend : friends)
    {
        if (_friend->status->value() == _status)
        {
            friendsWithStatus->append(_friend);
        }
    }
    return friendsWithStatus;
}

void FriendController::changeFriendStatus(const QString& friendReference, const models::Friend::eStatus _newStatus)
{
    Friend* _friend = getFriend(friendReference);
    changeFriendStatus(_friend, _newStatus);
}

void FriendController::changeFriendStatus(models::Friend* _friend, const models::Friend::eStatus _newStatus)
{
    if ( (_newStatus == Friend::eStatus::Online ||
          _newStatus == Friend::eStatus::Offline ||
          _newStatus == Friend::eStatus::Unknown ) &&
         (_friend != nullptr))
    {
        _friend->status->setValue(_newStatus);
        emit statusChanged();
        emit _friend->statusChanged();
    }
}

void FriendController::changeLastVisit(const QString& friendReference, const QDateTime& newLastVisit)
{
    Friend* _friend = getFriend(friendReference);
    if (_friend != nullptr)
    {
        _friend->lastVisit->setValue(newLastVisit);
        emit lastVisitChanged();
        emit _friend->lastVisitChanged();
    }
}

void FriendController::changeLastVisit(models::Friend* _friend, const QDateTime& newLastVisit)
{
    if (_friend != nullptr)
    {
        _friend->lastVisit->setValue(newLastVisit);
        emit lastVisitChanged();
        emit _friend->lastVisitChanged();
    }
}

}
}


