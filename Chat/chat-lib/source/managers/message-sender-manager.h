#ifndef MESSAGESENDERMANAGER_H
#define MESSAGESENDERMANAGER_H

#include <QObject>
#include <QQueue>
#include <QElapsedTimer>

#include <chat-lib_global.h>

#include <framework/worker.h>
#include <models/message.h>
#include <models/friend.h>
#include <managers/message-sender-queue-element.h>

namespace chat {
namespace managers {


class CHATLIBSHARED_EXPORT MessageSenderManager : public Worker
{
    Q_OBJECT
    
public:
    explicit MessageSenderManager(QObject *parent = nullptr);
    ~MessageSenderManager();
    void init(){}

signals:
    
    void finished();
    void error(QString err);
    
    //Data for Sending to Service Manager
    
    void MessageRecend(models::Message& message);
    //void CommonFriendListRequested(QString& friendName);
    void MessageStatusRequested(QString friendName, QString messageReference);
    void FriendStatusRequested(QString& friendName);
    
public slots:
    
    void process();
    
    //Received Data from ServiceManager
    
    void onMessageSend(models::Message& message);
    //void onCommonFriendListReceived(QList<models::Friend*> friends);
    void onMessageStatusReceived(QString& message, models::Message::eMessageStatus status);
    void onFriendStatusReceived(QString& friendName, models::Friend::eStatus status);

    bool ProcessMessage(MessageSenderQueueElement* elem);
    
private:
    bool isAbortProcess = false;
    QAtomicInteger<bool> Abort;

    QString currentUser;

    QQueue<MessageSenderQueueElement*> messagesForSend;

    MessageSenderQueueElement* elem;


    QAtomicInteger<bool> messageStatusSet = false;
    QAtomicInteger<bool> commonFriendListSet = false;
    QAtomicInteger<bool> friendStatusSet = false;

private:
    bool waitForMessageStatus();
    bool waitForFriendStatus();
    //bool waitForCommonFriendList();

    void clearData();

private:
    /*
    MessageSenderJob* job;
    MessageSenderJob* createJob(MessageSenderQueueElement message);
    void clearJobs();
    QElapsedTimer timer;
    */
    
};
    
    
}}

#endif // MESSAGESENDERMANAGER_H
