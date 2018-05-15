#include "chat-model.h"

using namespace chat::data;

namespace chat {
namespace models {

ChatModel::ChatModel(QObject* parent)
    : Entity(parent, "chat")
{
    reference = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "reference", "User Ref")));
    friendInChatReference = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "friendInChatReference", "Friend In Chat Reference")));
    messages = static_cast<EntityCollection<Message>*>(addChildCollection(new EntityCollection<Message>(this, "messages")));

    reference->setValue(this->id());
    setPrimaryKey(reference);
}

ChatModel::ChatModel(QObject *parent, const QJsonObject &json)
    : ChatModel(parent)
{
    update(json);
}

QQmlListProperty<Message> ChatModel::ui_messages()
{
    return QQmlListProperty<Message>(this, messages->derivedEntities());
}

void ChatModel::setFriendReference(Friend* _friendInChat)
{
    friendInChatReference->setValue(_friendInChat->reference->value());
}

void ChatModel::setFriendReference(QString& reference)
{
    friendInChatReference->setValue(reference);
}

void ChatModel::addMessage()
{
    messages->addEntity(new Message(this));
    emit messagesChanged();
}

}
}
