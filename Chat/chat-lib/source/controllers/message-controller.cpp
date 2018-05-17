#include "message-controller.h"

#include <QList>
#include <QDebug>

using namespace chat::models;

namespace chat {
namespace controllers {

class MessageController::Implementation
{
public:
    Implementation(MessageController* _messageController, UserModel* _user)
        : messageController(_messageController),
          user(_user)
    {
    }
    MessageController* messageController{nullptr};
    UserModel* user{nullptr};
};

MessageController::MessageController(QObject* parent, UserModel* _user)
    : QObject(parent)
{
    implementation.reset(new Implementation(this, _user));
}

MessageController::~MessageController()
{
}

void MessageController::addMessage(chat::models::ChatModel* _chat, const models::Message* _message )
{
    if (_chat != nullptr && _message != nullptr)
    {
        _chat->messages->addEntity(new Message(_chat, _message));

        emit messageAdded();
    }
}

void MessageController::addMessage(chat::models::ChatModel* _chat,
                                   const QString& reference,
                                   const QString& messageData,
                                   Message::eMessageType type,
                                   const QDateTime& _sendAt)
{
    if (_chat != nullptr)
    {
        QString sender;
        QString receiver;
        QDateTime sendAt = _sendAt;
        QDateTime receivedAt;
        Message::eMessageStatus status;

        if (type == Message::eMessageType::Incoming)
        {
            sender = _chat->friendInChatReference->value();
            receiver = implementation->user->reference->value();
            receivedAt = QDateTime::currentDateTime();
            status = Message::eMessageStatus::Delivered;
        }
        else if (type == Message::eMessageType::Outgoing)
        {
            sender = implementation->user->reference->value();
            receiver = _chat->friendInChatReference->value();
            sendAt = QDateTime::currentDateTime();
            receivedAt = QDateTime();
            status = Message::eMessageStatus::NotDelivered;
        }
        else
        {
            return;
        }

        Message* newMessage = new Message(_chat, reference, sender, receiver,
                                          sendAt, receivedAt, type, status, messageData);

        _chat->messages->addEntity(newMessage);

        emit messageAdded();
    }
}

void MessageController::addMessage(const QString& friendReference, const models::Message* _message )
{
    ChatModel* _chat = getChatByFriend(friendReference);
    if (_chat == nullptr)
    {
        _chat = new ChatModel(implementation->user);
        _chat->friendInChatReference->setValue(friendReference);
    }
    addMessage(_chat, _message);
}

void MessageController::addMessage(const QString& friendReference,
                                   const QString& reference,
                                   const QString& messageData,
                                   Message::eMessageType type,
                                   const QDateTime& sendAt)
{
    ChatModel* _chat = getChatByFriend(friendReference);
    if (_chat == nullptr)
    {
        _chat = new ChatModel(implementation->user);
        _chat->friendInChatReference->setValue(friendReference);
    }
    addMessage(_chat, reference, messageData, type, sendAt);
}

models::ChatModel* MessageController::getChatByFriend(const QString& friendReference) const
{
    QList<ChatModel*> chats = implementation->user->chats->derivedEntities();
    for (auto _chat : chats)
    {
        if (_chat->friendInChatReference->value() == friendReference)
        {
            return _chat;
        }
    }
    return nullptr;
}

models::Message* MessageController::getMessageByChat(const models::ChatModel* _chat, const QString &messageReference) const
{
    if (_chat != nullptr)
    {
        QList<Message*> messages = _chat->messages->derivedEntities();
        for (auto _message : messages)
        {
            if (_message->reference->value() == messageReference)
            {
                return _message;
            }
        }
    }
    return nullptr;
}
models::Message* MessageController::getMessageByFriend(const QString& friendReference, const QString &messageReference) const
{
    ChatModel* _chat = getChatByFriend(friendReference);
    if (_chat != nullptr)
    {
        return getMessageByChat(_chat, messageReference);
    }
    return nullptr;

}

models::Message* MessageController::getMessage(const QString& messageReference) const
{
    QList<ChatModel*> chats = implementation->user->chats->derivedEntities();
    for (auto _chat : chats)
    {
        Message* message = getMessageByChat(_chat, messageReference);
        if (message != nullptr)
        {
            return message;
        }
    }
    return nullptr;
}

models::Message::eMessageStatus MessageController::getMessageStatus(const QString& messageReference) const
{
    Message* message = getMessage(messageReference);
    if (message != nullptr)
    {
        return static_cast<Message::eMessageStatus>(message->messageStatus->value());
    }
    return Message::eMessageStatus::UnknownStat;
}


//Сломается, если сслыка на чат неверная
QList<models::Message*>& MessageController::getMessageList(const models::ChatModel* _chat) const
{
    return _chat->messages->derivedEntities();
}

QList<models::Message*>& MessageController::getMessageListByFriend(const models::Friend* _friend) const
{
    QString friendReference = _friend->reference->value();
    return getMessageListByFriend(friendReference);
}

//Сломается, если такого чата нет
QList<models::Message*>& MessageController::getMessageListByFriend(const QString& friendReference) const
{
    ChatModel* _chat = getChatByFriend(friendReference);
    return _chat->messages->derivedEntities();
}

QList<models::Message*>* MessageController::getMessageListByStatus(const models::ChatModel* _chat, models::Message::eMessageStatus _status) const
{
    if (_chat != nullptr)
    {
        QList<Message*> messages = getMessageList(_chat);
        return getMessageListByStatus(messages, _status);
    }
    return nullptr;
}

QList<models::Message*>* MessageController::getMessageListByStatus(const QList<models::Message*>& _messages, models::Message::eMessageStatus _status) const
{
    QList<Message*>* messageWithStatus = new QList<Message*>();
    for (auto _message : _messages)
    {
        if (_message->messageStatus->value() == _status)
        {
            messageWithStatus->append(_message);
        }
    }
    return messageWithStatus;
}

void MessageController::changeMessageStatus(const QString& messageReference, models::Message::eMessageStatus newStatus)
{
    Message* message = getMessage(messageReference);
    changeMessageStatus(message, newStatus);

}

void MessageController::changeMessageStatus(Message* message, Message::eMessageStatus newStatus)
{
    if (message != nullptr && (newStatus == Message::eMessageStatus::UnknownStat ||
                               newStatus == Message::eMessageStatus::NotDelivered ||
                               newStatus == Message::eMessageStatus::Delivered ||
                               newStatus == Message::eMessageStatus::Read))
    {
        message->messageStatus->setValue(newStatus);
        emit statusChanged();
    }
}




}
}


