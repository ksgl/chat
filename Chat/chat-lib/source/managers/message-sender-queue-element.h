#ifndef MESSAGESENDERQUEUEELEMENT_H
#define MESSAGESENDERQUEUEELEMENT_H

#include <QList>
#include <QQueue>
#include <QDateTime>

#include <models/message.h>
#include <models/friend.h>

namespace chat {
namespace managers {

struct MessageSenderQueueElement
{
    bool isForResending = false;
    bool isSharedWithFriends = false;

    QList<models::Friend*> commonFriends;
    QString receiver;
    models::Friend::eStatus status;
    models::Message::eMessageStatus mesStatus;

    models::Message message;

    MessageSenderQueueElement(){}

    MessageSenderQueueElement(models::Message& _message)
        : message(_message.parent(), &_message)
    {
        receiver = message.receiver->value();
        /*
        this->message.sender->setValue(_message.sender->value());
        this->message.receiver->setValue(_message.receiver->value());
        this->message.sendAt->setValue(_message.sendAt->value());
        this->message.receivedAt->setValue(_message.receivedAt->value());
        this->message.messageType->setValue(static_cast<models::Message::eMessageType>(_message.messageType->value()));
        this->message.messageStatus->setValue(static_cast<Message::eMessageStatus>(_message.messageStatus->value()));
        this->message.messageData->setValue(_message.messageData->value());
        */
    }

    MessageSenderQueueElement(MessageSenderQueueElement& other)
        : MessageSenderQueueElement(other.message)
    {
    }


};

}
}


#endif // MESSAGESENDERQUEUEELEMENT_H
