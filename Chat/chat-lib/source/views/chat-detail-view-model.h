#ifndef CHATDETAILVIEWMODEL_H
#define CHATDETAILVIEWMODEL_H

#include <QObject>

#include <chat-lib_global.h>
#include <models/chat-model.h>
#include <models/message.h>
#include <models/friend.h>

namespace chat {
namespace views {

class CHATLIBSHARED_EXPORT ChatDetailViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<chat::models::Message> ui_messages READ ui_messages NOTIFY messagesChanged)
    Q_PROPERTY(chat::models::Friend* ui_friend MEMBER _friend NOTIFY friendChanged)

public:
    ChatDetailViewModel(QObject* parent = nullptr);

    QQmlListProperty<chat::models::Message> ui_messages();
    QList<models::Message*> messages;
    models::ChatModel* chat;
    models::Friend* _friend;

signals:
    void messagesChanged();
    void friendChanged();
    void sendMessage(models::ChatModel* _chat, QString& messageData);

public slots:
    void sendMessageButtonClicked(QString messageData);
    void onMessagesAdded(models::Message* message);
    void SetMessages(QList<models::Message*> messages);
    void SetChat(models::ChatModel* chat);
    void SetFriend(models::Friend* _friend);
};



}
}


#endif // CHATDETAILVIEWMODEL_H
