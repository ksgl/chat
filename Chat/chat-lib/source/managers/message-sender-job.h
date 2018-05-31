/*
#ifndef MESSAGESENDERJOB_H
#define MESSAGESENDERJOB_H

#include <managers/message-sender-queue-element.h>
#include <framework/job.h>

#include <QObject>
#include <QRunnable>
#include <QAtomicInteger>

namespace chat {
namespace managers {

class MessageSenderJob : public framework::Job<MessageSenderQueueElement>
{
    Q_OBJECT
    
public:
    //explicit MessageSenderJob(QObject *parent = 0, MessageSenderQueueElement elem);
    void run() override;

    bool setCommonFriendList(QList<models::Friend> fiends);
    bool setMessageStatus(models::Message::eMessageStatus status);
    bool setFriendStatus(models::Friend::eStatus status);
    bool ProcessMessage();

signals:
    void jobCompleted() override;
    
public slots:
    void abort() = 0;


    
private:
    QAtomicInteger<bool> Abort;   
    MessageSenderQueueElement elem;
    QString currentUser;

    QAtomicInteger<bool> messageStatusSet = false;
    QAtomicInteger<bool> commonFriendListSet = false;
    QAtomicInteger<bool> friendStatusSet = false;
    
private:
    
    
    
};

}}

#endif // MESSAGESENDERJOB_H
*/
