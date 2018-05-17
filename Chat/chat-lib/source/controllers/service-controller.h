#ifndef SERVICECONTROLLER_H
#define SERVICECONTROLLER_H

#include <QObject>

#include <chat-lib_global.h>
#include <controllers/i-command-controller.h>
#include <controllers/i-user-controller.h>
#include <services/task-executor-callback-binder.h>

namespace chat {
namespace controllers {

class CHATLIBSHARED_EXPORT ServiceController : public QObject
{
    Q_OBJECT

public:
    explicit ServiceController(QObject *parent = nullptr,
                               ICommandController* _commandController = nullptr,
                               services::TaskExecutorCallbackBinder* _taskExecutorBinder = nullptr,
                               IUserController* _userController = nullptr);
    ~ServiceController();

signals:

public slots:

    /*------------------------------------------------------------------
     * BLOCK "COMMAND MANAGER" *
     * signals from GUI        *
     *------------------------------------------------------------------*/

    void onLoginCommandExecuted(QString data);
    void onRegisterCommandExecuted(QString data);
    //void onFindChatCommandExecuted();
    void onAddChatCommandExecuted(QString data);
    //void onRefreshChatListCommandExecuted();
    void onSendMessageCommandExecuted(QString data);
    //void onRefreshChatCommandExecuted();
    //void onFindFriendCommandExecuted();
    //void onRefreshFriendListCommandExecuted();
    void onFindNewFriendCommandExecuted(QString data);
    //void onAddToFriendsCommandExecuted();
    //void onConfirmFriendRequest();
    //void onDeclineFriendRequest();
    void onExitCommandExecuted();

    /*------------------------------------------------------------------
     * BLOCK "NETMESSAGE MANAGER" *
     * signals from TaskExecutor  *
     *------------------------------------------------------------------*/

    void onLoginAnswerReceivedExecuted(QString data);
    void onRegisterAnswerReceivedExecuted(QString data);
    void onFriendReceiverExecuted(QString data);
    void onMessageReceivedExecuted(QString data);

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;
};



}
}


#endif // SERVICECONTROLLER_H
