#ifndef SERVICECONTROLLER_H
#define SERVICECONTROLLER_H

#include <QObject>

#include <chat-lib_global.h>
//#include <json.h>
#include <controllers/i-command-controller.h>
#include <controllers/i-user-controller.h>
#include <services/task-executor-callback-binder.h>
#include <managers/message-sender-manager.h>
#include <controllers/view-controller.h>

#include <task-exec/TaskExecutor.hpp>
#include <task-exec/json.hpp>

namespace chat {
namespace controllers {

class CHATLIBSHARED_EXPORT ServiceController : public QObject
{
    Q_OBJECT

public:
    explicit ServiceController(QObject *parent = nullptr,
                               ICommandController* _commandController = nullptr,
                               services::TaskExecutorCallbackBinder* _taskExecutorBinder = nullptr,
                               IUserController* _userController = nullptr,
                               ViewController* _viewCpntroller = nullptr);
    ~ServiceController();

    void empty_func(nlohmann::json json);

public slots:

    /*------------------------------------------------------------------
     * BLOCK "GUI MANAGER" *
     * signals from GUI        *
     *------------------------------------------------------------------*/

    void GUI_onLoginCommandExecuted(QString& login, QString& password);
    void GUI_onRegisterCommandExecuted(QString& login, QString& password);
    void GUI_onChatDetailViewRequested(QString chatReference);
    //void onFindChatCommandExecuted();
    void GUI_onAddChatCommandExecuted(QString data);
    //void onRefreshChatListCommandExecuted();
    void GUI_onSendMessageCommandExecuted(models::ChatModel* chat, QString& data);
    //void onRefreshChatCommandExecuted();
    //void onFindFriendCommandExecuted();
    //void onRefreshFriendListCommandExecuted();
    void GUI_onFindNewFriendCommandExecuted(QString data);
    //void onAddToFriendsCommandExecuted();
    void GUI_onExitCommandExecuted();
    void GUI_onFriendListViewRequested();
    void GUI_onChatListViewRequested();

    /*------------------------------------------------------------------
     * BLOCK "NETMESSAGE MANAGER" *
     * signals from TaskExecutor  *
     *------------------------------------------------------------------*/

    void NET_onLoginAnswerReceivedExecuted(models::PayloadModel&);
    void NET_onRegisterAnswerReceivedExecuted(models::PayloadModel&);
    void NET_onFriendReceiverExecuted(models::PayloadModel&);
    void NET_onMessageReceivedExecuted(models::PayloadModel&);
    
    /*------------------------------------------------------------------
     * BLOCK "MESSAGE SENDER MANAGER" *
     * signals from MessageSender Thread  *
     *------------------------------------------------------------------*/

public slots:
    void MS_onMessageSendSignal(models::Message& message);
    void MS_onCommonFriendListRequestedSignal(QString& friendName);
    void MS_onMessageStatusRequestedSignal(QString friendName, QString messageReference);
    void MS_onFriendStatusRequestedSignal(QString& friendName);

signals: // to MessageSender Thread
    void MS_sendMessageToQueue(models::Message& message);
    void MS_sendCommondFriendList(QList<models::Friend*> friends);
    void MS_sendMessageStatus(QString& message, models::Message::eMessageStatus status);
    void MS_sendFriendStatus(QString& friendName, models::Friend::eStatus status);

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;
};



}
}


#endif // SERVICECONTROLLER_H
