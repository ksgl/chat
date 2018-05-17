#include "user-model.h"

using namespace chat::data;

namespace chat {
namespace models {

UserModel::UserModel(QObject* parent)
    : Entity(parent, "user")
{
    reference = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "reference", "User Ref")));
    name = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "name", "Name")));
    publicKey = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "publicKey", "Public Key")));
    
    friends = static_cast<EntityCollection<Friend>*>(addChildCollection(new EntityCollection<Friend>(this, "friends")));
    chats = static_cast<EntityCollection<ChatModel>*>(addChildCollection(new EntityCollection<ChatModel>(this, "chats")));
    
    setPrimaryKey(reference);
}

UserModel::UserModel(QObject *parent, const QJsonObject &json)
    : UserModel(parent)
{
    update(json);
}

QQmlListProperty<Friend> UserModel::ui_friends()
{
    return QQmlListProperty<Friend>(this, friends->derivedEntities());
}

QQmlListProperty<ChatModel> UserModel::ui_chats()
{
    return QQmlListProperty<ChatModel>(this, chats->derivedEntities());
}

void UserModel::addFriend()
{
    friends->addEntity(new Friend(this));
    emit friendsChanged();
}

void UserModel::addChat(Friend* friendInChat)
{
    ChatModel* newChat = new ChatModel(this);
    newChat->setFriendReference(friendInChat);
    chats->addEntity(newChat);

    emit chatsChanged();
}


}
}

