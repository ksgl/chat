#include "message.h"

using namespace chat::data;

namespace chat {
namespace models {

std::map<int, QString> Message::messageTypeMapper = std::map<int, QString> {
    { Message::eMessageType::Unknown, "" },
    { Message::eMessageType::Incoming, "Incoming"},
    { Message::eMessageType::Outgoing, "Outgoing"}
};

std::map<int, QString> Message::messageStatusMapper = std::map<int, QString> {
    { Message::eMessageStatus::UnknownStat, "" },
    { Message::eMessageStatus::NotDelivered, "Not Delivered"},
    { Message::eMessageStatus::Delivered, "Delivered"},
    { Message::eMessageStatus::Read, "Read"}
};

Message::Message(QObject *parent)
    : Entity(parent, "message")
{
    reference = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "reference", "User Ref")));

    messageType = static_cast<EnumeratorDecorator*>(addDataItem(new EnumeratorDecorator(this, "messageType", "Message Type", 0, messageTypeMapper)));
    messageStatus = static_cast<EnumeratorDecorator*>(addDataItem(new EnumeratorDecorator(this, "messageStatus", "Message Status", 0, messageStatusMapper)));

    sender = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "from" ,"from")));
    receiver = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "to", "to")));
    receiver_ip = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "to_ip", "to_ip")));
    sendAt = static_cast<DateTimeDecorator*>(addDataItem(new DateTimeDecorator(this, "sendAt", "Send At")));
    receivedAt = static_cast<DateTimeDecorator*>(addDataItem(new DateTimeDecorator(this, "receivedAt", "Received At")));

    messageData = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "text", "text")));

    reference->setValue(this->id());
    setPrimaryKey(reference);
}

Message::Message(QObject *parent, const QJsonObject &json)
    : Message(parent)
{
    update(json);
}

Message::Message(QObject *parent, const Message* other)
    : Message(parent)
{
    QString newReference = other->reference->value();
    QString newSender = other->sender->value();
    QString newReceiver = other->receiver->value();
    QDateTime newSendAt = other->sendAt->value();
    QDateTime newReceivedAt = other->receivedAt->value();
    Message::eMessageType type = static_cast<Message::eMessageType>(other->messageType->value());
    Message::eMessageStatus status = static_cast<Message::eMessageStatus>(other->messageStatus->value());
    QString data = other->messageData->value();

    if (!newReference.isEmpty())
    {
        this->reference->setValue(newReference);
    }
    this->sender->setValue(newSender);
    this->receiver->setValue(newReceiver);
    this->sendAt->setValue(newSendAt);
    this->receivedAt->setValue(newReceivedAt);
    this->messageType->setValue(type);
    this->messageStatus->setValue(status);
    this->messageData->setValue(data);
}

Message::Message(QObject *parent, const Message& other)
    : Message(parent)
{
    QString newReference = other.reference->value();
    QString newSender = other.sender->value();
    QString newReceiver = other.receiver->value();
    QDateTime newSendAt = other.sendAt->value();
    QDateTime newReceivedAt = other.receivedAt->value();
    Message::eMessageType type = static_cast<Message::eMessageType>(other.messageType->value());
    Message::eMessageStatus status = static_cast<Message::eMessageStatus>(other.messageStatus->value());
    QString data = other.messageData->value();

    if (!newReference.isEmpty())
    {
        this->reference->setValue(newReference);
    }
    this->sender->setValue(newSender);
    this->receiver->setValue(newReceiver);
    this->sendAt->setValue(newSendAt);
    this->receivedAt->setValue(newReceivedAt);
    this->messageType->setValue(type);
    this->messageStatus->setValue(status);
    this->messageData->setValue(data);
}

Message::Message(QObject *parent, const QString& newReference,
                                  const QString& newSender,
                                  const QString& newReceiver,
                                  const QDateTime& newSendAt,
                                  const QDateTime& newReceivedAt,
                                  Message::eMessageType newMessageType,
                                  Message::eMessageStatus newMessageStatus,
                                  const QString& newMessageData)
    : Message(parent)
{
    if (!newReference.isEmpty())
    {
        this->reference->setValue(newReference);
    }
    this->sender->setValue(newSender);
    this->receiver->setValue(newReceiver);
    this->sendAt->setValue(newSendAt);
    this->receivedAt->setValue(newReceivedAt);
    this->messageType->setValue(newMessageType);
    this->messageStatus->setValue(newMessageStatus);
    this->messageData->setValue(newMessageData);
}


}
}

