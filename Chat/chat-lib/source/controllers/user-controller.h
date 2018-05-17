#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include <QObject>
#include <QScopedPointer>

#include <chat-lib_global.h>
#include <controllers/i-user-controller.h>
#include <models/user-model.h>
#include <models/friend.h>
#include <models/message.h>
#include <models/chat-model.h>

#include <controllers/friend-controller.h>
#include <controllers/message-controller.h>

namespace chat {
namespace controllers {

class CHATLIBSHARED_EXPORT UserController : public IUserController
{
    Q_OBJECT

public:
    explicit UserController(QObject *parent = nullptr,
                            FriendController* _friendCOntroller = nullptr,
                            MessageController* _messageController = nullptr,
                            models::UserModel* user = nullptr);
    ~UserController();

    //const models::UserModel* currentUser() const;
    void setUser(chat::models::UserModel* _newUser);

public:

    /*------------------------------------------------------------------
     * BLOCK "FRIEND MANAGER" *
     *------------------------------------------------------------------*/

    void addFriend(const chat::models::Friend* _friend);
    void addFriend(const QString& reference, const QString& friendName, const QString& friendIp,
                           const models::Friend::eStatus _status, const QDateTime& lastVisit);

    models::Friend* getFriend(const QString& friendReference) const;
    models::Friend* getFriendByName(const QString& friendName) const;
    models::Friend::eStatus getFriendStatus(const QString& friendReference) const;
    QList<models::Friend*>& getFriendList() const;
    QList<models::Friend*>* getFriendListByStatus(const models::Friend::eStatus status) const;

    void changeFriendStatus(const QString& friendReference, const models::Friend::eStatus _newStatus);
    void changeFriendStatus(models::Friend* _friend, const models::Friend::eStatus _newStatus);
    void changeLastVisit(const QString& friendReference, const QDateTime& newLastVisit);
    void changeLastVisit(models::Friend* _friend, const QDateTime& newLastVisit);

    /*------------------------------------------------------------------
     * BLOCK "CHAT MANAGER" *
     *------------------------------------------------------------------*/

    /*
    void addChat(const chat::models::Friend* _friend);
    void addChat(const QString& friendReference);

    //models::ChatModel* getChat(const QString& chatReference) const override;
    //models::ChatModel* getChatByFriend(const QString& friendReference) const;
    //models::ChatModel* getChatByFriendName(const QString& friendName) const;
    //models::ChatModel* getChatByFriend(const models::Friend* _friend) const;
    QList<models::ChatModel*>& getChats() const;
    */

    /*------------------------------------------------------------------
     * BLOCK "MESSAGE MANAGER" *
     *------------------------------------------------------------------*/

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
    models::Message* getMessage(const QString& messageReference) const = 0;
    models::Message::eMessageStatus getMessageStatus(const QString& messageReference) const;
    QList<models::Message*>& getMessageList(const models::ChatModel* _chat) const;
    QList<models::Message*>& getMessageListByFriend(const models::Friend* _friend) const;
    QList<models::Message*>& getMessageListByFriend(const QString& friendReference) const;
    QList<models::Message*>* getMessageListByStatus(const models::ChatModel* _chat, models::Message::eMessageStatus _status) const;
    QList<models::Message*>* getMessageListByStatus(const QList<models::Message*>& _messages, models::Message::eMessageStatus _status) const;

    void changeMessageStatus(const QString& messageReference, models::Message::eMessageStatus newStatus);
    void changeMessageStatus(models::Message* message, models::Message::eMessageStatus newStatus);

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;
};

}
}


#endif // USERCONTROLLER_H
