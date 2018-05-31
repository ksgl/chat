#include "user-controller.h"

#include <controllers/database-controller.h>

#include <QList>
#include <QDebug>
#include <QJsonDocument>

using namespace chat::models;

namespace chat {
namespace controllers {

class UserController::Implementation
{
public:
    Implementation(UserController* _userController, UserModel* _user)
        : userController(_userController), user(_user)
    {
        databaseController = new DatabaseController(userController);
        friendController = new FriendController(_userController, user);
        messageController = new MessageController(_userController, user);
    }

    UserController* userController{nullptr};
    FriendController* friendController{nullptr};
    MessageController* messageController{nullptr};
    UserModel* user{nullptr};

    IDatabaseController* databaseController{nullptr};
};

UserController::UserController(QObject *parent, UserModel* _user)
    : IUserController(), QObject(parent)
{
    implementation.reset(new Implementation(this, _user));
}

UserController::~UserController(){}

void UserController::uploadUser(QString userName)
{
    QJsonArray users = implementation->databaseController->find("users", userName);
    if (users.count() == 0)
    {
        implementation->user->name->setValue(userName);
        implementation->databaseController->createRow("users", userName, implementation->user->toJson());
    }
    else
    {
        implementation->user->update(users.at(0).toObject());
        setUser(implementation->user);
    }
}

void UserController::setUser(UserModel* _newUser)
{
    implementation.reset(new Implementation(this, _newUser));
}

const models::UserModel* UserController::currentUser() const
{
    return implementation->user;
}

QString UserController::currentUserName() const
{
    return implementation->user->name->value();
}

/*------------------------------------------------------------------
 * BLOCK "FRIEND MANAGER" *
 *------------------------------------------------------------------*/

void UserController::addFriend(const chat::models::Friend* _friend)
{
    implementation->friendController->addFriend(_friend);
    implementation->databaseController->updateRow("users", implementation->user->name->value(), implementation->user->toJson());
}

void UserController::addFriend(const QString& reference, const QString& friendName, const QString& friendIp,
                       const models::Friend::eStatus _status, const QDateTime& lastVisit)
{
    implementation->friendController->addFriend(reference, friendName, friendIp, _status, lastVisit);
    implementation->databaseController->updateRow("users", implementation->user->name->value(), implementation->user->toJson());
}

models::Friend* UserController::getFriend(const QString& friendReference) const
{
    models::Friend* _friend = implementation->friendController->getFriend(friendReference);
    return _friend;
}

models::Friend* UserController::getFriendByName(const QString& friendName) const
{
    return implementation->friendController->getFriendByName(friendName);
}

models::Friend::eStatus UserController::getFriendStatus(const QString& friendReference) const
{
    return implementation->friendController->getFriendStatus(friendReference);
}

QList<models::Friend*>& UserController::getFriendList() const
{
    return implementation->friendController->getFriendList();
}

QList<models::Friend*>* UserController::getFriendListByStatus(const models::Friend::eStatus status) const
{
    return implementation->friendController->getFriendListByStatus(status);
}

void UserController::changeFriendStatus(const QString& friendReference, const models::Friend::eStatus _newStatus)
{
    implementation->friendController->changeFriendStatus(friendReference, _newStatus);
}

void UserController::changeFriendStatus(models::Friend* _friend, const models::Friend::eStatus _newStatus)
{
    implementation->friendController->changeFriendStatus(_friend, _newStatus);
}

void UserController::changeLastVisit(const QString& friendReference, const QDateTime& newLastVisit)
{
    implementation->friendController->changeLastVisit(friendReference, newLastVisit);
}

void UserController::changeLastVisit(models::Friend* _friend, const QDateTime& newLastVisit)
{
    implementation->friendController->changeLastVisit(_friend, newLastVisit);
}

/*------------------------------------------------------------------
 * BLOCK "CHAT MANAGER" *
 *------------------------------------------------------------------*/

/*
void UserController::addChat(const chat::models::Friend* _friend) {}
void UserController::addChat(const QString& friendReference) {}
*/

models::ChatModel* UserController::getChat(const QString& chatReference) const
{
    QList<ChatModel*> chats = implementation->user->chats->derivedEntities();
    for (auto _chat : chats)
    {
        if (_chat->reference->value() == chatReference)
        {
            return _chat;
        }
    }
    return nullptr;
}

/*
//models::ChatModel* UserController::getChatByFriend(const QString& friendReference) const {}
models::ChatModel* UserController::getChatByFriendName(const QString& friendName) const {}
//models::ChatModel* UserController::getChatByFriend(const models::Friend* _friend) const {}
*/

QList<models::ChatModel*>& UserController::getChatList() const
{
    return implementation->user->chats->derivedEntities();
}


/*------------------------------------------------------------------
 * BLOCK "MESSAGE MANAGER" *
 *------------------------------------------------------------------*/

void UserController::addMessage(chat::models::ChatModel* _chat, const models::Message* _message )
{
    implementation->messageController->addMessage(_chat, _message);
    implementation->databaseController->updateRow("users", implementation->user->name->value(), implementation->user->toJson());
}

void UserController::addMessage(chat::models::ChatModel* _chat, const QString& reference,
                                                      const QString& messageData,
                                                      models::Message::eMessageType type,
                                                      const QDateTime& sendAt)
{
    implementation->messageController->addMessage(_chat, reference, messageData, type, sendAt);
    implementation->databaseController->updateRow("users", implementation->user->name->value(), implementation->user->toJson());
}

void UserController::addMessage(const QString& friendReference, const models::Message* _message )
{
    implementation->messageController->addMessage(friendReference, _message);
    implementation->databaseController->updateRow("users", implementation->user->name->value(), implementation->user->toJson());
}

void UserController::addMessage(const QString& friendReference, const QString& reference,
                                                const QString& messageData,
                                                models::Message::eMessageType type,
                                                const QDateTime& sendAt)
{
    implementation->messageController->addMessage(friendReference, reference, messageData, type, sendAt);
    implementation->databaseController->updateRow("users", implementation->user->name->value(), implementation->user->toJson());
}

models::ChatModel* UserController::getChatByFriend(const QString& friendReference) const
{
    return implementation->messageController->getChatByFriend(friendReference);
}

models::Message* UserController::getMessageByChat(const models::ChatModel* _chat, const QString& messageReference) const
{
    return implementation->messageController->getMessageByChat(_chat, messageReference);
}

models::Message* UserController::getMessageByFriend(const QString& friendReference, const QString& messageReference) const
{
    return implementation->messageController->getMessageByFriend(friendReference, messageReference);
}

models::Message* UserController::getMessage(const QString& messageReference) const
{
    return implementation->messageController->getMessage(messageReference);
}

models::Message::eMessageStatus UserController::getMessageStatus(const QString& messageReference) const
{
    return implementation->messageController->getMessageStatus(messageReference);
}

QList<models::Message*>& UserController::getMessageList(const models::ChatModel* _chat) const
{
    return implementation->messageController->getMessageList(_chat);
}

QList<models::Message*>& UserController::getMessageListByFriend(const models::Friend* _friend) const
{
    return implementation->messageController->getMessageListByFriend(_friend);
}

QList<models::Message*>& UserController::getMessageListByFriend(const QString& friendReference) const
{
    return implementation->messageController->getMessageListByFriend(friendReference);
}

QList<models::Message*>* UserController::getMessageListByStatus(const models::ChatModel* _chat, models::Message::eMessageStatus _status) const
{
    return implementation->messageController->getMessageListByStatus(_chat, _status);
}

QList<models::Message*>* UserController::getMessageListByStatus(const QList<models::Message*>& _messages, models::Message::eMessageStatus _status) const
{
    return implementation->messageController->getMessageListByStatus(_messages, _status);
}

void UserController::changeMessageStatus(const QString& messageReference, models::Message::eMessageStatus newStatus)
{
    implementation->messageController->changeMessageStatus(messageReference, newStatus);
}

void UserController::changeMessageStatus(models::Message* message, models::Message::eMessageStatus newStatus)
{
    implementation->messageController->changeMessageStatus(message, newStatus);
}

}
}

