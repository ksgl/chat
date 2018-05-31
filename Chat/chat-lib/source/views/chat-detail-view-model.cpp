#include "chat-detail-view-model.h"

namespace chat {
namespace views {

ChatDetailViewModel::ChatDetailViewModel(QObject* parent)
    : QObject(parent)
{
}

QQmlListProperty<chat::models::Message> ChatDetailViewModel::ui_messages()
{
    return QQmlListProperty<chat::models::Message>(this, messages);
}

void ChatDetailViewModel::onMessagesAdded(models::Message* message)
{
    messages.push_back(message);
    emit messagesChanged();
}

void ChatDetailViewModel::SetMessages(QList<models::Message *> _messages)
{
    messages = _messages;
    emit messagesChanged();
}

void ChatDetailViewModel::SetChat(models::ChatModel* _chat)
{
    if (_chat != nullptr)
    {
        chat = _chat;
        messages = _chat->messages->derivedEntities();
        emit messagesChanged();
    }
}

void ChatDetailViewModel::SetFriend(models::Friend *_friend)
{
    if (_friend != nullptr)
    {
        this->_friend = _friend;
        emit friendChanged();
    }
}

void ChatDetailViewModel::sendMessageButtonClicked(QString messageData)
{
    emit sendMessage(chat, messageData);
}

}
}

