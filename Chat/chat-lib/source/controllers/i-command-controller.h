#ifndef ICOMMANDCONTROLLER_H
#define ICOMMANDCONTROLLER_H

#include <QObject>
#include <QtQml/QQmlListProperty>
#include <framework/command.h>
#include <models/chat-model.h>

#include <chat-lib_global.h>

namespace chat {
namespace controllers {

class CHATLIBSHARED_EXPORT ICommandController : public QObject
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
    ICommandController(QObject* parent = nullptr) : QObject(parent){}
    virtual ~ICommandController(){}
    
    virtual QQmlListProperty<framework::Command> ui_loginViewContextCommands() = 0;
    virtual QQmlListProperty<framework::Command> ui_registrationViewContextCommands() = 0;
    virtual QQmlListProperty<framework::Command> ui_chatListViewContextCommands() = 0;
    virtual QQmlListProperty<framework::Command> ui_exitViewContextCommands() = 0;
    virtual QQmlListProperty<framework::Command> ui_friendListViewContextCommands() = 0;
    virtual QQmlListProperty<framework::Command> ui_addFriendViewContextCommands() = 0;
    virtual QQmlListProperty<framework::Command> ui_chatViewContextCommands() = 0;

public slots:

    virtual void onLoginExecuted() = 0;
    virtual void onLoginViewExecuted() = 0;
    virtual void onRegisterViewExecuted() = 0;
    virtual void onRegisterExecuted() = 0;
    virtual void onFindChatExecuted() = 0;
    virtual void onAddChatExecuted() = 0;
    virtual void onRefreshChatListExecuted() = 0;
    virtual void onSendMessageExecuted() = 0;
    virtual void onRefreshChatExecuted() = 0;
    virtual void onFindFriendExecuted() = 0;
    virtual void onAddFriendViewExecuted() = 0;
    virtual void onRefreshFriendListExecuted() = 0;
    virtual void onFindNewFriendExecuted() = 0;
    virtual void onAddToFriendsExecuted() = 0;
    virtual void onExitExecuted() = 0;
    virtual void onChatListViewExecuted() = 0;
    virtual void onChatDetailViewExecuted() = 0;
    virtual void onFriendListViewExcuted() = 0;
    virtual void onGoToFriendListView() = 0;
    virtual void onGoToChatListView() = 0;

signals:

    virtual void LoginCommandExecuted(QString data) = 0;
    virtual void RegisterCommandExecuted(QString data) =0;
    //virtual void FindChatCommandExecuted(QString data);
    virtual void AddChatCommandExecuted(QString data) = 0;
    //virtual void RefreshChatListCommandExecuted(Qstring data);
    virtual void SendMessageCommandExecuted(QString data) = 0;
    //void RefreshChatCommandExecuted(QString data);
    //void FindFriendCommandExecuted(QString data);
    //void RefreshFriendListCommandExecuted(QString data);
    virtual void FindNewFriendCommandExecuted(QString data) = 0;
    //void AddToFriendsCommandExecuted(QString data);
    //void ConfirmFriendRequest(QString data);
    //void DeclineFriendRequest(QString data);
    virtual void ExitCommandExecuted() = 0;
    void friendListViewRequested();
    void chatListViewRequested();

};

}
}

#endif // ICOMMANDCONTROLLER_H
