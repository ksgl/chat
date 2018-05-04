#ifndef COMMANDCONTROLLER_H
#define COMMANDCONTROLLER_H

#include <QObject>
#include <QtQml/QQmlListProperty>

#include <chat-lib_global.h>
#include <framework/command.h>
#include <controllers/i-command-controller.h>
#include <controllers/i-navigation-controller.h>

namespace chat {
namespace controllers {

class CHATLIBSHARED_EXPORT CommandController : public ICommandController
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<chat::framework::Command> ui_loginViewContextCommands READ ui_loginViewContextCommands CONSTANT)
    Q_PROPERTY(QQmlListProperty<chat::framework::Command> ui_registrationViewContextCommands READ ui_registrationViewContextCommands CONSTANT)
    Q_PROPERTY(QQmlListProperty<chat::framework::Command> ui_chatListViewContextCommands READ ui_chatListViewContextCommands CONSTANT)
    Q_PROPERTY(QQmlListProperty<chat::framework::Command> ui_friendListViewContextCommands READ ui_friendListViewContextCommands CONSTANT)
    Q_PROPERTY(QQmlListProperty<chat::framework::Command> ui_addFriendViewContextCommands READ ui_addFriendViewContextCommands CONSTANT)
    Q_PROPERTY(QQmlListProperty<chat::framework::Command> ui_chatViewContextCommands READ ui_chatViewContextCommands CONSTANT)
    Q_PROPERTY(QQmlListProperty<chat::framework::Command> ui_exitViewContextCommands READ ui_exitViewContextCommands CONSTANT)

public:
    explicit CommandController(QObject* _parent = nullptr, INavigationController* _navigationController = nullptr);
    ~CommandController();

    QQmlListProperty<framework::Command> ui_loginViewContextCommands();
    QQmlListProperty<framework::Command> ui_registrationViewContextCommands();
    QQmlListProperty<framework::Command> ui_chatListViewContextCommands();
    QQmlListProperty<framework::Command> ui_exitViewContextCommands();
    QQmlListProperty<framework::Command> ui_friendListViewContextCommands();
    QQmlListProperty<framework::Command> ui_addFriendViewContextCommands();
    QQmlListProperty<framework::Command> ui_chatViewContextCommands();

signals:

public slots:
    void onLoginExecuted();
    void onLoginViewExecuted();
    void onRegisterViewExecuted();
    void onRegisterExecuted();
    void onFindChatExecuted();
    void onAddChatExecuted();
    void onRefreshChatListExecuted();
    void onSendMessageExecuted();
    void onRefreshChatExecuted();
    void onFindFriendExecuted();
    void onAddFriendViewExecuted();
    void onRefreshFriendListExecuted();
    void onFindNewFriendExecuted();
    void onAddToFriendsExecuted();
    void onRequestsFriendsViewExecuted();
    void onResponcesFriendsViewExecuted();
    void onConfirmFriendRequest();
    void onDeclineFriendRequest();
    void onExitExecuted();

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;
};

}
}



#endif // COMMANDCONTROLLER_H
