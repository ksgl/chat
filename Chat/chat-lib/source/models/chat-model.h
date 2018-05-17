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
    
public:
    explicit ChatModel(QObject *parent = nullptr);
    ChatModel(QObject* parent, const QJsonObject& json);
    
    data::StringDecorator* reference{nullptr};
    data::StringDecorator* friendInChatReference{nullptr};

    data::EntityCollection<Message>* messages{nullptr};
    
    QQmlListProperty<chat::models::Message> ui_messages();
    
signals:
    void messagesChanged();

public slots:
    void addMessage();
    void setFriendReference(Friend* _friendInChat);
    void setFriendReference(QString& reference);
    void sendMessage(QString& message);
};


}
}


#endif // CHATMODEL_H
