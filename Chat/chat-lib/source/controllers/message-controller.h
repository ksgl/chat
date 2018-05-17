#ifndef MESSAGECONTROLLER_H
#define MESSAGECONTROLLER_H

#include <QObject>
#include <QString>
#include <QScopedPointer>

#include <chat-lib_global.h>
#include <models/message.h>
#include <models/user-model.h>
#include <models/chat-model.h>

namespace chat {
namespace controllers {

class CHATLIBSHARED_EXPORT MessageController : public QObject
{
    Q_OBJECT

public:

    explicit MessageController(QObject* parent = nullptr, models::UserModel* _user = nullptr);
    ~MessageController();

public:

    void addMessage(chat::models::ChatModel* _chat, const models::Message* _message );
    void addMessage(chat::models::ChatModel* _chat, const QString& reference,
                                                          const QString& messageData,
                                                          models::Message::eMessageType type,
                                                          const QDateTime& sendAt);

    void addMessage(const QString& friendReference, const models::Message* _message );
    void addMessage(const QString& friendReference, const QString& reference,
                                                    const QString& messageData,
                                                    models::Message::eMessageType type,
                                                    const QDateTime& sendAt);

    models::ChatModel* getChatByFriend(const QString& friendReference) const;
    models::Message* getMessageByChat(const models::ChatModel* _chat, const QString &messageReference) const;
    models::Message* getMessageByFriend(const QString& friendReference, const QString &messageReference) const;
    models::Message* getMessage(const QString& messageReference) const;
    models::Message::eMessageStatus getMessageStatus(const QString& messageReference) const;
    //Ломается, если неправильная ссылка
    QList<models::Message*>& getMessageList(const models::ChatModel* _chat) const;
    //Ломается, если нет такого друга
    QList<models::Message*>& getMessageListByFriend(const models::Friend* _friend) const;
    //Ломается, если нет такого друга
    QList<models::Message*>& getMessageListByFriend(const QString& friendReference) const;
    QList<models::Message*>* getMessageListByStatus(const models::ChatModel* _chat, models::Message::eMessageStatus _status) const;
    QList<models::Message*>* getMessageListByStatus(const QList<models::Message*>& _messages, models::Message::eMessageStatus _status) const;

    void changeMessageStatus(const QString& messageReference, models::Message::eMessageStatus newStatus);
    void changeMessageStatus(models::Message* message, models::Message::eMessageStatus newStatus);

signals:

    void messageAdded();
    void statusChanged();
    void lastVisitChanged();

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;
};

}}
#endif // MESSAGECONTROLLER_H
