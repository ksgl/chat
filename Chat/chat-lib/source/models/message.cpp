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

    sender = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "sender" ,"Sender")));
    receiver = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "receiver", "Receiver")));

    sendAt = static_cast<DateTimeDecorator*>(addDataItem(new DateTimeDecorator(this, "sendAt", "Send At")));
    receivedAt = static_cast<DateTimeDecorator*>(addDataItem(new DateTimeDecorator(this, "receivedAt", "Received At")));

    messageData = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "messageData", "Message Data")));

    setPrimaryKey(reference);
}

Message::Message(QObject *parent, const QJsonObject &json)
    : Message(parent)
{
    update(json);
}

void Message::changeMessageStatus(eMessageStatus newStatus)
{
    this->messageStatus->setValue(newStatus);
    emit messageStatusChanged();
}

void Message::changeMessageStatus(QString newStatus)
{
    for (auto pair : messageStatusMapper) {
        if (pair.second == newStatus) {
            this->messageStatus->setValue(pair.first);
            emit messageStatusChanged();
            break;
        }
    }
}

}
}

