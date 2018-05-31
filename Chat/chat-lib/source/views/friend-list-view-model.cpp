#include "friend-list-view-model.h"

using namespace chat::models;

namespace chat {
namespace views {

FriendListViewModel::FriendListViewModel(QObject* parent)
    : QObject(parent)
{
}

QQmlListProperty<chat::models::Friend> FriendListViewModel::ui_friends()
{
    return QQmlListProperty<Friend>(this, friends);
}

void FriendListViewModel::SetFriends(QList<Friend *> _friends)
{
    friends = _friends;
}

void FriendListViewModel::onFriendAdded(Friend *newFriend)
{
    friends.append(newFriend);
    emit friendAddedToView();
}

void FriendListViewModel::onFriendChanged(Friend* _friend)
{
    for (QList<Friend*>::Iterator it = friends.begin(); it != friends.end(); it++)
    {
        if ((*it)->friendName->value() == _friend->friendName->value())
        {
            (*it)->status->value() == _friend->status->value();
            (*it)->lastVisit->value() == _friend->lastVisit->value();
            emit friendsChanged();
            break;
        }
    }
}

}
}

