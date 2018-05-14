#ifndef IUSERCONTROLLER_H
#define IUSERCONTROLLER_H

#include <QObject>
#include <QString>
#include <QScopedPointer>

#include <chat-lib_global.h>

#include <models/user-model.h>
#include <models/chat-model.h>
#include <models/friend.h>
#include <models/message.h>

namespace chat {
namespace controllers {

class CHATLIBSHARED_EXPORT IUserController : public QObject
{
    Q_OBJECT

public:
    IUserController(QObject* parent = nullptr) : QObject(parent){}
    virtual ~IUserController(){}

    const models::UserModel* currentUser() const;

public slots:

    virtual void switchUser(chat::models::UserModel* _newUser) = 0;

    /*------------------------------------------------------------------
     * BLOCK "FRIEND MANAGER" *
     *------------------------------------------------------------------*/

    virtual void addFriend(const chat::models::Friend* _friend) = 0;
    virtual void addFriend(const QString& friendName, const QString& friendIp, const QDateTime& lastVisit) = 0;

    virtual models::Friend* getFriend(const QString& friendReference) const = 0;
    virtual models::Friend* getFriendByName(const QString& friendName) const = 0;
    virtual models::Friend::eStatus getFriendStatus(const QString& friendReference) const = 0;
    virtual QList<models::Friend*>& getFriendList() const = 0;
    virtual QList<models::Friend*>& getFriendListByStatus(const models::Friend::eStatus status) const = 0;

    virtual void changeFriendStatus(const QString& friendReference, const models::Friend::eStatus _newStatus) = 0;
    virtual void changeFriendStatus(models::Friend* _friend, const models::Friend::eStatus _newStatus) = 0;
    virtual void changeLastVisit(const QString& friendREference, const QDateTime& newLastVisit) = 0;
    virtual void changeLastVisit(models::Friend* _friend, const QDateTime& newLastVisit) = 0;

    /*------------------------------------------------------------------
     * BLOCK "CHAT MANAGER" *
     *------------------------------------------------------------------*/

    virtual void addChat(const chat::models::Friend* _friend) = 0;
    virtual void addChat(const QString& friendReference) = 0;

    virtual models::ChatModel* getChat(const QString& chatReference) const = 0;
    virtual models::ChatModel* getChatByFriend(const QString& friendReference) const = 0;
    virtual models::ChatModel* getChatByFriendName(const QString& friendName) const = 0;
    virtual models::ChatModel* getChatByFriend(const models::Friend* _friend) const = 0;
    virtual QList<models::ChatModel*>& getChats() const = 0;

    /*------------------------------------------------------------------
     * BLOCK "MESSAGE MANAGER" *
     *------------------------------------------------------------------*/

    virtual void addMessage(const chat::models::ChatModel* _chat, const models::Message* _message ) = 0;
    virtual void addMessage(const chat::models::ChatModel* _chat, const QString& messageData ) = 0;
    virtual void addMessage(const QString& friendReference, const models::Message* _message ) = 0;
    virtual void addMessage(const QString& friendReference, const QString& messageData, models::Message::eMessageType _type ) = 0;

    virtual models::Message* getMessage(const QString& messageReference) const = 0;
    virtual models::Message::eMessageStatus getMessageStatus(const QString& messageReference) const = 0;
    virtual QList<models::Message*>& getMessageList(const models::ChatModel* _chat) const = 0;
    virtual QList<models::Message*>& getMessageListByFriend(const models::Friend* _friend) const = 0;
    virtual QList<models::Message*>& getMessageListByFriend(const QString& friendReference) const = 0;
    virtual QList<models::Message*>& getMessageListByStatus(const models::ChatModel* _chat, const models::Message::eMessageStatus _status) const = 0;
    virtual QList<models::Message*>& getMessageListByStatus(const QList<models::Message*>& _messages) const = 0;

    virtual void changeMessageStatus(const QString& messageReference, models::Message::eMessageStatus newStatus) = 0;

};

}
}

#endif // IUSERCONTROLLER_H
