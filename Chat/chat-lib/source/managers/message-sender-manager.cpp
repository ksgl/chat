#include "message-sender-manager.h"
#include <QDebug>
#include <QThreadPool>
#include <QTimer>

#include "managers/message-sender-job.h"
#include "managers/message-sender-queue-element.h"

using namespace chat::models;

namespace chat {
namespace managers {

MessageSenderManager::MessageSenderManager(QObject *parent) : Worker(parent)
{
}

MessageSenderManager::~MessageSenderManager()
{
}

void MessageSenderManager::onMessageSend(models::Message& message)
{
    // Проверка наличия в списке
    MessageSenderQueueElement* elem = new MessageSenderQueueElement(message);
    messagesForSend.enqueue(elem);
}

/*
void MessageSenderManager::onCommonFriendListReceived(QList<Friend *> friends)
{
    if (elem != nullptr)
    {
        elem->commonFriends = friends;
        commonFriendListSet = true;
    }
}
*/

void MessageSenderManager::onMessageStatusReceived(QString& message, Message::eMessageStatus status)
{
    if (elem != nullptr)
    {
        elem->mesStatus = status;
        messageStatusSet = true;
    }
}

void MessageSenderManager::onFriendStatusReceived(QString& friendName, Friend::eStatus status)
{
    if (elem != nullptr)
    {
        elem->status = status;
        friendStatusSet = true;
    }
}

void MessageSenderManager::process()
{
    while (!isAbortProcess)
    {
        if (messagesForSend.count() > 0)
        {
            clearData();
            elem = messagesForSend.dequeue();
            if (!ProcessMessage(elem))
            {
                // Логика обработки ошибок
                messagesForSend.enqueue(elem);
            }
        }
        else
        {
            // Ожидание (пауза)
            // Чтобы избежать постоянного опроса пустой очереди
            QTimer timer(this);
            timer.setInterval(2000);
            while (timer.isActive()){}
        }
    }
    emit finished();
}

void MessageSenderManager::clearData()
{
    isAbortProcess = false;
    messageStatusSet = false;
    commonFriendListSet = false;
    friendStatusSet = false;

    if( elem != nullptr)
    {
        delete elem;
        elem = nullptr;
    }
}

bool  MessageSenderManager::ProcessMessage(MessageSenderQueueElement* elem)
{
    if (elem->message.sender->value() != currentUser )
    {
        elem->isForResending == true;
    }

    // Проверить статус сообщения не для пересылки
    // удалить, если статус "Delivered" или "Read"
    // иначе - продолжить

    if (!elem->isForResending)
    {
        emit MessageStatusRequested(elem->receiver, elem->message.reference->value());
        if (!waitForMessageStatus())
        {
            return false;
        }
        else
        {
            if (elem->message.messageStatus->value() == Message::eMessageStatus::Delivered ||
                elem->message.messageStatus->value() == Message::eMessageStatus::Read   )
            {
                return true;
            }
        }
    }

    // Проверить статус друга, если онлайн - отослать ему и положить сообщение в конец
    // (удалим при следующей проверке статуса "Delivered" или "Read"
    // Иначе - продолжить

    emit FriendStatusRequested(elem->receiver);
    if (!waitForFriendStatus())
    {
        return false;
    }
    else
    {
        if(elem->status == Friend::eStatus::Online)
        {
            emit MessageRecend(elem->message);
            messagesForSend.enqueue(elem);
            return true;
        }
    }

    /*
    // Запрашиваем список общих друзей онлайн, пересылаем им
    // Не делаем ничего, если сообщение для пересылки или уже расслылалось

    if (!elem->isForResending && !elem->isSharedWithFriends)
    {
        emit CommonFriendListRequested(elem->receiver);
        if (!waitForCommonFriendList())
        {
            return false;
        }
        else
        {
            for (auto _friend : elem->commonFriends)
            {
                emit MessageRecend(elem->message);
            }
            messagesForSend.enqueue(elem);
            return true;
        }
    }
    */

    return false;
}

bool MessageSenderManager::waitForMessageStatus()
{
    QTimer timer(this);
    timer.setInterval(6000);               //6 секунд на операцию взятия статуса
    timer.start();

    //Ждем ответа статуса
    while (timer.isActive() && !messageStatusSet)
    {
    }

    if (!messageStatusSet)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool MessageSenderManager::waitForFriendStatus()
{
    QTimer timer(this);
    timer.setInterval(6000);               //6 секунд на операцию взятия статуса
    timer.start();

    //Ждем ответа статуса
    while (timer.isActive() && !friendStatusSet)
    {
    }

    if (!friendStatusSet)
    {
        return false;
    }
    else
    {
        return true;
    }
}

/*
bool MessageSenderManager::waitForCommonFriendList()
{
    QTimer timer(this);
    timer.setInterval(8000);               //8 секунд на операцию взятия друзей
    timer.start();

    //Ждем ответа статуса
    while (timer.isActive() && !commonFriendListSet)
    {
    }

    if (!commonFriendListSet)
    {
        return false;
    }
    else
    {
        return true;
    }
}
*/




}
}

