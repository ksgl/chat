 #ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>

#include <chat-lib_global.h>
#include <data/datetime-decorator.h>
#include <data/string-decorator.h>
#include <data/enumerator-decorator.h>
#include <data/entity.h>

namespace chat {
namespace models {

class CHATLIBSHARED_EXPORT Message : public data::Entity
{
    Q_OBJECT
    Q_PROPERTY(chat::data::StringDecorator* ui_reference MEMBER reference CONSTANT)
    Q_PROPERTY(chat::data::StringDecorator* ui_sender MEMBER sender CONSTANT)
    Q_PROPERTY(chat::data::DateTimeDecorator* ui_sendAt MEMBER sendAt CONSTANT)
    Q_PROPERTY(chat::data::DateTimeDecorator* ui_receivedAt MEMBER receivedAt CONSTANT)
    Q_PROPERTY(chat::data::StringDecorator* ui_messageData MEMBER messageData CONSTANT)
    Q_PROPERTY(chat::data::EnumeratorDecorator* ui_messageType MEMBER messageType CONSTANT)
    Q_PROPERTY(chat::data::EnumeratorDecorator* ui_messageStatus MEMBER messageStatus NOTIFY messageStatusChanged)
    
public:
    enum eMessageType {
        Unknown = 0,
        Incoming,
        Outgoing
    };
    
    enum eMessageStatus {
        UnknownStat = 0,
        NotDelivered,
        Delivered,
        Read
    };
    
public:
    explicit Message(QObject *parent = nullptr);
    Message(QObject *parent, const QJsonObject& json);
    Message(QObject *parent, const Message* other);
    Message(QObject *parent, const Message& other);

    Message(QObject *parent, const QString& reference,
                             const QString& sender,
                             const QString& receiver,
                             const QDateTime& sendAt,
                             const QDateTime& receivedAt,
                             Message::eMessageType messageType,
                             Message::eMessageStatus messageStatus,
                             const QString& messageData);
    
    data::StringDecorator* reference{nullptr};

    data::StringDecorator* sender{nullptr};
    data::StringDecorator* receiver_ip{nullptr};
    data::StringDecorator* receiver{nullptr};
    
    data::DateTimeDecorator* sendAt{nullptr};
    data::DateTimeDecorator* receivedAt{nullptr};
    
    data::EnumeratorDecorator* messageType{nullptr};
    data::EnumeratorDecorator* messageStatus{nullptr};
    
    data::StringDecorator* messageData{nullptr};
    
    static std::map<int, QString> messageTypeMapper;
    static std::map<int, QString> messageStatusMapper;

signals:
    void messageStatusChanged();

};

}
}

#endif // MESSAGE_H
