#include "command-controller.h"

#include <QList>
#include <QDebug>

using namespace chat::framework;

namespace chat {
namespace controllers {

class CommandController::Implementation
{
public:
    Implementation(CommandController* _commandController,
                   INavigationController* _navigationController)
        : commandController(_commandController),
          navigationController(_navigationController)
    {
        Command* loginCommand = new Command(commandController, QChar( 0xf0c7 ), "Login");
        QObject::connect( loginCommand, &Command::executed, commandController, &CommandController::onLoginExecuted);
        loginViewContextCommands.append(loginCommand);

        Command* registerViewCommand = new Command(commandController, QChar(0xf0c7), "Registration");
        QObject::connect(registerViewCommand, &Command::executed, commandController, &CommandController::onRegisterViewExecuted);
        loginViewContextCommands.append(registerViewCommand);

        Command* registerCommand = new Command(commandController, QChar(0xf0c7), "Register");
        QObject::connect(registerCommand, &Command::executed, commandController, &CommandController::onRegisterExecuted);
        registrationViewContextCommands.append(registerCommand);

        Command* backToLoginCommand = new Command(commandController, QChar(0xf0c7), "Back to Login");
        QObject::connect(backToLoginCommand, &Command::executed, commandController, &CommandController::onLoginViewExecuted);
        registrationViewContextCommands.append(backToLoginCommand);

        Command* findChatCommand = new Command(commandController, QChar(0xf0c7), "Find Chat");
        QObject::connect(findChatCommand, &Command::executed, commandController, &CommandController::onFindChatExecuted);
        chatListViewContexCommands.append(findChatCommand);

        Command* addChatCommand = new Command(commandController, QChar(0xf0c7), "Add Chat");
        QObject::connect(addChatCommand, &Command::executed, commandController, &CommandController::onAddChatExecuted);
        chatListViewContexCommands.append(addChatCommand);

        Command* refreshChatListCommand = new Command(commandController, QChar(0xf0c7), "Refresh");
        QObject::connect(refreshChatListCommand, &Command::executed, commandController, &CommandController::onRefreshChatListExecuted);
        chatListViewContexCommands.append(refreshChatListCommand);

        Command* sendMessageCommand = new Command(commandController, QChar(0xf0c7), "Send");
        QObject::connect(sendMessageCommand, &Command::executed, commandController, &CommandController::onSendMessageExecuted);
        chatViewContextCommands.append(sendMessageCommand);

        Command* refreshChatCommand = new Command(commandController, QChar(0xf0c7), "Refresh Chat");
        QObject::connect(refreshChatCommand, &Command::executed, commandController, &CommandController::onRefreshChatExecuted);
        chatViewContextCommands.append(refreshChatCommand);

        Command* findFriendCommand = new Command(commandController, QChar(0xf0c7), "Find Friend");
        QObject::connect(findFriendCommand, &Command::executed, commandController, &CommandController::onFindFriendExecuted);
        friendListViewContextCommands.append(findFriendCommand);

        Command* addFriendViewCommand = new Command(commandController, QChar(0xf0c7), "Add Friend");
        QObject::connect(addFriendViewCommand, &Command::executed, commandController, &CommandController::onAddFriendViewExecuted);
        friendListViewContextCommands.append(addFriendViewCommand);

        Command* refreshFriendListCommand = new Command(commandController, QChar(0xf0c7), "Refresh");
        QObject::connect(refreshFriendListCommand, &Command::executed, commandController, &CommandController::onRefreshFriendListExecuted);
        friendListViewContextCommands.append(refreshFriendListCommand);

        Command* findNewFriendCommand = new Command(commandController, QChar(0xf0c7), "Find New Friend");
        QObject::connect(findNewFriendCommand, &Command::executed, commandController, &CommandController::onFindNewFriendExecuted);
        addFriendViewContextCommands.append(findNewFriendCommand);

        Command* addToFriendsCommand = new Command(commandController, QChar(0xf0c7), "Add To Friends");
        QObject::connect(addToFriendsCommand, &Command::executed, commandController, &CommandController::onAddToFriendsExecuted);
        addFriendViewContextCommands.append(addToFriendsCommand);

        Command* requestsFriendsViewCommand = new Command(commandController, QChar(0xf0c7), "Friend Requests");
        QObject::connect(requestsFriendsViewCommand, &Command::executed, commandController, &CommandController::onRequestsFriendsViewExecuted);
        addFriendViewContextCommands.append(requestsFriendsViewCommand);

        Command* responcesFriendsViewCommand = new Command(commandController, QChar(0xf0c7), "Friends Responces");
        QObject::connect(responcesFriendsViewCommand, &Command::executed, commandController, &CommandController::onResponcesFriendsViewExecuted);
        addFriendViewContextCommands.append(responcesFriendsViewCommand);

        Command* confirmFriendRequest = new Command(commandController, QChar(0xf0c7), "Confirm Request");
        QObject::connect(confirmFriendRequest, &Command::executed, commandController, &CommandController::onConfirmFriendRequest);
        addFriendViewContextCommands.append(confirmFriendRequest);

        Command* declineFriendRequest = new Command(commandController, QChar(0xf0c7), "Decline Request");
        QObject::connect(declineFriendRequest, &Command::executed, commandController, &CommandController::onDeclineFriendRequest);
        addFriendViewContextCommands.append(declineFriendRequest);

        Command* exitCommand = new Command(commandController, QChar(0xf0c7), "Exit");
        QObject::connect(exitCommand, &Command::executed, commandController, &CommandController::onExitExecuted);
        exitViewContextCommands.append(exitCommand);
    }

    CommandController* commandController{nullptr};
    INavigationController* navigationController{nullptr};

    QList<Command*> loginViewContextCommands{};
    QList<Command*> registrationViewContextCommands{};
    QList<Command*> chatListViewContexCommands{};
    QList<Command*> chatViewContextCommands{};
    QList<Command*> friendListViewContextCommands{};
    QList<Command*> addFriendViewContextCommands{};
    QList<Command*> exitViewContextCommands{};

};

CommandController::CommandController(QObject *parent, INavigationController *navigationController)
    : ICommandController(parent)
{
    implementation.reset(new Implementation(this, navigationController));
}

CommandController::~CommandController(){}

QQmlListProperty<Command> CommandController::ui_loginViewContextCommands()
{
    return QQmlListProperty<Command>(this, implementation->loginViewContextCommands);
}

QQmlListProperty<Command> CommandController::ui_registrationViewContextCommands()
{
    return QQmlListProperty<Command>(this, implementation->registrationViewContextCommands);
}

QQmlListProperty<Command> CommandController::ui_chatListViewContextCommands()
{
    return QQmlListProperty<Command>(this, implementation->chatListViewContexCommands);
}

QQmlListProperty<Command> CommandController::ui_exitViewContextCommands()
{
    return QQmlListProperty<Command>(this, implementation->exitViewContextCommands);
}

QQmlListProperty<Command> CommandController::ui_friendListViewContextCommands()
{
    return QQmlListProperty<Command>(this, implementation->friendListViewContextCommands);
}

QQmlListProperty<Command> CommandController::ui_addFriendViewContextCommands()
{
    return QQmlListProperty<Command>(this, implementation->addFriendViewContextCommands);
}

QQmlListProperty<Command> CommandController::ui_chatViewContextCommands()
{
    return QQmlListProperty<Command>(this, implementation->chatViewContextCommands);
}

void CommandController::onLoginExecuted()
{
    qDebug() << "You executed the LOGIN command!";
    QString data = "Login and Password Data From GUI";
    implementation->commandController->LoginCommandExecuted(data);
    //implementation->navigationController->goChatListView();
}

void CommandController::onRegisterExecuted()
{
    qDebug() << "You executed the REGISTER command!";
    QString data = "Login and Password Data From GUI";
    implementation->commandController->RegisterCommandExecuted(data);
    //implementation->navigationController->goChatListView();
}

void CommandController::onFindChatExecuted()
{
    qDebug() << "You executed the FIND_CHAT command!";
}

void CommandController::onAddChatExecuted()
{
    qDebug() << "You executed the ADD_CHAT command!";
    QString data = "Friend Reference From GUI";
    implementation->commandController->AddChatCommandExecuted(data);
}

void CommandController::onRefreshChatListExecuted()
{
    qDebug() << "You executed the REFRESH_CHAT_LIST command!";
}

void CommandController::onSendMessageExecuted()
{
    qDebug() << "You executed the SEND_MESSAGE command!";
    QString data = "Message data from GUI";
    implementation->commandController->SendMessageCommandExecuted(data);
}

void CommandController::onRefreshChatExecuted()
{
    qDebug() << "You executed the FIND_CHAT command!";
}

void CommandController::onFindFriendExecuted()
{
    qDebug() << "You executed the FIND_FRIEND command!";
}

void CommandController::onAddFriendViewExecuted()
{
    implementation->navigationController->goAddFriendView();
}

void CommandController::onRefreshFriendListExecuted()
{
    qDebug() << "You executed the REFRESH_FRIEND_LIST command!";
}

void CommandController::onFindNewFriendExecuted()
{
    qDebug() << "You executed the FIND_NEW_FRIEND command!";
    QString data = "Friend Name from GUI";
    implementation->commandController->FindNewFriendCommandExecuted(data);
}

void CommandController::onAddToFriendsExecuted()
{
    qDebug() << "You executed the ADD_TO_FRIENDS command!";
}

void CommandController::onConfirmFriendRequest()
{
    qDebug() << "You executed the CONFIRM_REQUEST command!";
}

void CommandController::onDeclineFriendRequest()
{
    qDebug() << "You executed the DECLINE_REQUEST command!";
}

void CommandController::onExitExecuted()
{
    implementation->commandController->ExitCommandExecuted();
    implementation->navigationController->goLoginView();
}

void CommandController::onLoginViewExecuted()
{
    qDebug() << "You executed the GO_TO_LOGIN command!";
    implementation->navigationController->goLoginView();
}

void CommandController::onChatListViewExecuted()
{
    implementation->navigationController->goChatListView();
}

void CommandController::onRegisterViewExecuted()
{
    implementation->navigationController->goRegistrationView();
}

void CommandController::onRequestsFriendsViewExecuted()
{
    implementation->navigationController->goRequestsFriendsView();
}

void CommandController::onResponcesFriendsViewExecuted()
{
    implementation->navigationController->goResponcesFriendsView();
}

}
}
