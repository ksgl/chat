#ifndef CHATMODEL_H
#define CHATMODEL_H

#include <QObject>
#include <QtQml/QQmlListProperty>

#include <chat-lib_global.h>
#include <data/string-decorator.h>
#include <models/message.h>
#include <models/friend.h>

namespace chat {
namespace models {

class CHATLIBSHARED_EXPORT ChatModel : public data::Entity
{
    Q_OBJECT
    Q_PROPERTY( chat::data::StringDecorator* ui_reference MEMBER reference CONSTANT)
    Q_PROPERTY( chat::data::StringDecorator* ui_friendInChatReference MEMBER friendInChatReference CONSTANT)
    Q_PROPERTY( QQmlListProperty<chat::models::Message> ui_messages READ ui_messages NOTIFY messagesChanged )
    Q_PROPERTY( chat::data::StringDecorator* ui_friendInChatName MEMBER friendInChatName CONSTANT)
    Q_PROPERTY( chat::models::Message* ui_lastMessage MEMBER lastMessage CONSTANT)

public:
    explicit ChatModel(QObject *parent = nullptr);
    ChatModel(QObject* parent, const QJsonObject& json);
    
    data::StringDecorator* reference{nullptr};
    data::StringDecorator* friendInChatReference{nullptr};
    data::StringDecorator* friendInChatName{nullptr};
    models::Message* lastMessage{nullptr};

    data::EntityCollection<Message>* messages{nullptr};
    
    QQmlListProperty<chat::models::Message> ui_messages();
    
signals:
    void messagesChanged();
    void lastMessageChanged();

public slots:
    void onMessagesChanged();

};


}
}


#endif // CHATMODEL_H
