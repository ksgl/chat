#include "service-controller.h"

#include <framework/worker.h>
#include <views/login-view-model.h>
#include <controllers/user-controller.h>
#include <models/net-command-model.h>
#include <views/login-view-model.h>
#include <views/registration-view-model.h>
#include <services/task-former-service.h>

#include <QThread>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>

typedef std::function<void(const nlohmann::json&)> Callback;

using namespace chat::services;
using namespace chat::managers;

namespace chat {
namespace controllers {

class ServiceController::Implementation
{
public:
    Implementation(ServiceController* _serviceController,
                   ICommandController* _commandController,
                   TaskExecutorCallbackBinder* _taskExecutorBinder,
                   ViewController* _viewController)
        : serviceController(_serviceController),
          commandController(_commandController),
          taskExecutorBinder(_taskExecutorBinder),
          viewController(_viewController)
    {
        QObject::connect( viewController->loginViewModel, &views::LoginViewModel::LoginReceived, serviceController, &ServiceController::GUI_onLoginCommandExecuted);
        QObject::connect( viewController->registrationViewModel, &views::RegistrationViewModel::RegistrationReceived, serviceController, &ServiceController::GUI_onRegisterCommandExecuted);
        QObject::connect( viewController->chatListModelView, &views::ChatListModelView::gui_chatDetailViewRequested, serviceController, &ServiceController::GUI_onChatDetailViewRequested);
        QObject::connect( commandController, &ICommandController::AddChatCommandExecuted, serviceController, &ServiceController::GUI_onAddChatCommandExecuted);
        QObject::connect( commandController, &ICommandController::FindNewFriendCommandExecuted, serviceController, &ServiceController::GUI_onFindNewFriendCommandExecuted);
        QObject::connect( viewController->chatDetailViewModel, &views::ChatDetailViewModel::sendMessage, serviceController, &ServiceController::GUI_onSendMessageCommandExecuted);
        QObject::connect( commandController, &ICommandController::ExitCommandExecuted, serviceController, &ServiceController::GUI_onExitCommandExecuted);
        QObject::connect( commandController, &ICommandController::friendListViewRequested, serviceController, &ServiceController::GUI_onFriendListViewRequested);
        QObject::connect( commandController, &ICommandController::chatListViewRequested, serviceController, &ServiceController::GUI_onChatListViewRequested);

        QObject::connect( taskExecutorBinder, &TaskExecutorCallbackBinder::LoginAnswerReceived, serviceController, &ServiceController::NET_onLoginAnswerReceivedExecuted);
        QObject::connect( taskExecutorBinder, &TaskExecutorCallbackBinder::RegisterAnswerReceived, serviceController, &ServiceController::NET_onLoginAnswerReceivedExecuted);
        QObject::connect( taskExecutorBinder, &TaskExecutorCallbackBinder::FriendReceived, serviceController, &ServiceController::NET_onFriendReceiverExecuted);
        QObject::connect( taskExecutorBinder, &TaskExecutorCallbackBinder::MessageReceived, serviceController, &ServiceController::NET_onMessageReceivedExecuted);

        t_MessageSenderManager = new QThread;
        MS_Manager = new managers::MessageSenderManager(nullptr);
        MS_Manager->moveToThread(t_MessageSenderManager);

        QObject::connect(t_MessageSenderManager, &QThread::started, MS_Manager, &MessageSenderManager::process);
        QObject::connect(MS_Manager, &MessageSenderManager::finished, t_MessageSenderManager, &QThread::quit);

        QObject::connect(serviceController, &ServiceController::MS_sendMessageToQueue, MS_Manager, &MessageSenderManager::onMessageSend);
        //QObject::connect(serviceController, &ServiceController::MS_sendCommondFriendList, MS_Manager, &MessageSenderManager::onCommonFriendListReceived);
        QObject::connect(serviceController, &ServiceController::MS_sendMessageStatus, MS_Manager, &MessageSenderManager::onMessageStatusReceived);
        QObject::connect(serviceController, &ServiceController::MS_sendFriendStatus, MS_Manager, &MessageSenderManager::onFriendStatusReceived);

        QObject::connect(MS_Manager, &MessageSenderManager::MessageRecend, serviceController, &ServiceController::MS_onMessageSendSignal);
        //QObject::connect(MS_Manager, &MessageSenderManager::CommonFriendListRequested, serviceController, &ServiceController::MS_onCommonFriendListRequestedSignal);
        QObject::connect(MS_Manager, &MessageSenderManager::MessageStatusRequested, serviceController, &ServiceController::MS_onMessageStatusRequestedSignal);
        QObject::connect(MS_Manager, &MessageSenderManager::FriendStatusRequested, serviceController, &ServiceController::MS_onFriendStatusRequestedSignal);

        t_MessageSenderManager->start();

        taskFormerService = new TaskFormerService(serviceController);
    }

    ServiceController* serviceController{nullptr};
    ICommandController* commandController{nullptr};
    TaskExecutorCallbackBinder* taskExecutorBinder{nullptr};
    IUserController* userController{nullptr};
    ViewController* viewController{nullptr};
    TaskFormerService* taskFormerService{nullptr};

    QThread t_FriendManager{nullptr};
    QThread* t_MessageSenderManager{nullptr};
    managers::MessageSenderManager *MS_Manager{nullptr};
};

ServiceController::ServiceController(QObject *parent, ICommandController* _commandController, TaskExecutorCallbackBinder* _taskExecutorBinder,
                                     IUserController* _userController, ViewController* _viewController)
    : QObject(parent)
{
    implementation.reset(new Implementation(this, _commandController, _taskExecutorBinder, _viewController));
}

ServiceController::~ServiceController()
{
    QObject::disconnect( implementation->viewController->loginViewModel, &views::LoginViewModel::LoginReceived, implementation->serviceController, &ServiceController::GUI_onLoginCommandExecuted);
    QObject::disconnect( implementation->viewController->registrationViewModel, &views::RegistrationViewModel::RegistrationReceived, implementation->serviceController, &ServiceController::GUI_onRegisterCommandExecuted);
    QObject::disconnect( implementation->commandController, &ICommandController::AddChatCommandExecuted, implementation->serviceController, &ServiceController::GUI_onAddChatCommandExecuted);
    QObject::disconnect( implementation->commandController, &ICommandController::FindNewFriendCommandExecuted, implementation->serviceController, &ServiceController::GUI_onFindNewFriendCommandExecuted);
    //QObject::disconnect( implementation->commandController, &ICommandController::SendMessageCommandExecuted, implementation->serviceController, &ServiceController::GUI_onSendMessageCommandExecuted);
    QObject::disconnect( implementation->commandController, &ICommandController::ExitCommandExecuted, implementation->serviceController, &ServiceController::GUI_onExitCommandExecuted);

    QObject::disconnect( implementation->taskExecutorBinder, &TaskExecutorCallbackBinder::LoginAnswerReceived, implementation->serviceController, &ServiceController::NET_onLoginAnswerReceivedExecuted);
    QObject::disconnect( implementation->taskExecutorBinder, &TaskExecutorCallbackBinder::RegisterAnswerReceived, implementation->serviceController, &ServiceController::NET_onLoginAnswerReceivedExecuted);
    QObject::disconnect( implementation->taskExecutorBinder, &TaskExecutorCallbackBinder::FriendReceived, implementation->serviceController, &ServiceController::NET_onFriendReceiverExecuted);
    QObject::disconnect( implementation->taskExecutorBinder, &TaskExecutorCallbackBinder::MessageReceived, implementation->serviceController, &ServiceController::NET_onMessageReceivedExecuted);

    QObject::disconnect( implementation->t_MessageSenderManager, &QThread::started,  implementation->MS_Manager, &MessageSenderManager::process);
    QObject::disconnect( implementation->MS_Manager, &MessageSenderManager::finished,  implementation->t_MessageSenderManager, &QThread::quit);

    QObject::disconnect(this, &ServiceController::MS_sendMessageToQueue, implementation->MS_Manager, &MessageSenderManager::onMessageSend);
    //QObject::disconnect(this, &ServiceController::MS_sendCommondFriendList, implementation->MS_Manager, &MessageSenderManager::onCommonFriendListReceived);
    QObject::disconnect(this, &ServiceController::MS_sendMessageStatus, implementation->MS_Manager, &MessageSenderManager::onMessageStatusReceived);
    QObject::disconnect(this, &ServiceController::MS_sendFriendStatus, implementation->MS_Manager, &MessageSenderManager::onFriendStatusReceived);

    QObject::disconnect( implementation->MS_Manager, &MessageSenderManager::MessageRecend, implementation->serviceController, &ServiceController::MS_onMessageSendSignal);
    //QObject::disconnect( implementation->MS_Manager, &MessageSenderManager::CommonFriendListRequested, implementation->serviceController, &ServiceController::MS_onCommonFriendListRequestedSignal);
    QObject::disconnect( implementation->MS_Manager, &MessageSenderManager::MessageStatusRequested, implementation->serviceController, &ServiceController::MS_onMessageStatusRequestedSignal);
    QObject::disconnect( implementation->MS_Manager, &MessageSenderManager::FriendStatusRequested, implementation->serviceController, &ServiceController::MS_onFriendStatusRequestedSignal);
    
    implementation->t_MessageSenderManager->quit();
    implementation->t_MessageSenderManager->wait(1000);
    if (!implementation->t_MessageSenderManager->isFinished())
    {
        implementation->t_MessageSenderManager->terminate();
    }
}

void ServiceController::GUI_onLoginCommandExecuted(QString& login, QString& password)
{
    implementation->viewController->loginViewModel->changeState(views::LoginViewModel::WaitingForServerAnswer);
    QJsonObject& netTask = implementation->taskFormerService->formLoginTask(login, password);
    implementation->taskExecutorBinder->sendNetTask( netTask );
}

void ServiceController::GUI_onRegisterCommandExecuted(QString& login, QString& password)
{
    implementation->viewController->registrationViewModel->changeState(views::RegistrationViewModel::WaitingForServerAnswer);
    QJsonObject& netTask = implementation->taskFormerService->formRegisterTask(login, password);
    implementation->taskExecutorBinder->sendNetTask( netTask );
}


void ServiceController::GUI_onChatDetailViewRequested(QString chatReference)
{
    models::ChatModel* _chat = implementation->userController->getChat(chatReference);
    if (_chat != nullptr)
    {
        models::Friend* _friend = implementation->userController->getFriend(_chat->friendInChatReference->value());
        implementation->viewController->chatDetailViewModel->SetChat(_chat);
        implementation->viewController->chatDetailViewModel->SetFriend(_friend);
        implementation->commandController->onChatDetailViewExecuted();
    }
}

void ServiceController::GUI_onFriendListViewRequested()
{
    QList<models::Friend*> friends = implementation->userController->getFriendList();
    implementation->viewController->friendListViewModel->SetFriends(friends);
    implementation->commandController->onGoToFriendListView();
}

void ServiceController::GUI_onChatListViewRequested()
{
    QList<models::ChatModel*> chats = implementation->userController->getChatList();
    implementation->viewController->chatListModelView->SetChats(chats);
    implementation->commandController->onGoToChatListView();
}

void ServiceController::GUI_onAddChatCommandExecuted(QString friendName)
{
    //QString friendReference = implementation->rawStringParser->parseFriendReference(data);
    models::Friend* _friend = implementation->userController->getFriendByName(friendName);
    if (_friend  != nullptr)
    {
        //implementation->userController->addChat(_friend);
    }
    else
    {
        //Process FriendNotFound
    }
}

void ServiceController::empty_func(nlohmann::json json){}

void ServiceController::GUI_onSendMessageCommandExecuted(models::ChatModel* chat, QString& data)
{
    models::Message* message = new models::Message(chat);
    models::Friend* _friend = implementation->userController->getFriendByName(chat->friendInChatName->value());
    message->sender->setValue(implementation->userController->currentUserName());
    message->receiver->setValue(chat->friendInChatName->value());
    message->receiver_ip->setValue(_friend->friendIp->value());
    message->sendAt->setValue(QDateTime::currentDateTime());
    message->messageType->setValue(models::Message::eMessageType::Outgoing);
    message->messageStatus->setValue(models::Message::eMessageStatus::NotDelivered);
    message->messageData->setValue(data);

    implementation->userController->addMessage(chat->friendInChatReference->value(), message);
    implementation->viewController->chatDetailViewModel->onMessagesAdded(message);

    emit MS_sendMessageToQueue(*message);
}

void ServiceController::GUI_onFindNewFriendCommandExecuted(QString friendName)
{
    QJsonObject& netTask = implementation->taskFormerService->formFriendRequestTask(friendName);
    implementation->taskExecutorBinder->sendNetTask( netTask );
}

void ServiceController::GUI_onExitCommandExecuted()
{
    /*
    QJsonObject netTask = taskFormerService->formExitTask(data);
    taskHandlerSenderService->sendNetTask( netTask );
    */
}

void ServiceController::NET_onLoginAnswerReceivedExecuted(models::PayloadModel& payload)
{
    int logineResult = payload.loginData->loginStatus->value(); // 0 - ok, 1 - error, 2 - user exists
    switch (logineResult) {
    case 0:
        emit implementation->viewController->loginViewModel->changeState(views::LoginViewModel::SuccessfulAuthorization);
        implementation->userController->uploadUser(payload.loginData->login->value());
        GUI_onChatListViewRequested();
        break;

    case 1:
        emit implementation->viewController->loginViewModel->changeState(views::LoginViewModel::Error_OtherError);
        break;

    default:
        emit implementation->viewController->loginViewModel->changeState(views::LoginViewModel::Error_OtherError);
        break;
    }
}

void ServiceController::NET_onRegisterAnswerReceivedExecuted(models::PayloadModel& payload)
{
    int registerResult = payload.loginData->loginStatus->value(); // 0 - ok, 1 - error, 2 - user exists
    switch (registerResult) {
    case 0:
        emit implementation->viewController->registrationViewModel->changeState(views::RegistrationViewModel::SuccessfulAuthorization);
        break;

    case 1:
        emit implementation->viewController->registrationViewModel->changeState(views::RegistrationViewModel::Error_OtherError);
        break;

    case 2:
        emit implementation->viewController->registrationViewModel->changeState(views::RegistrationViewModel::Error_UserExists);
        break;

    default:
        emit implementation->viewController->registrationViewModel->changeState(views::RegistrationViewModel::Error_OtherError);
        break;
    }

}

/* Если пришел новый друг - добавляем, старый - обновляем */
void ServiceController::NET_onFriendReceiverExecuted(models::PayloadModel& payload)
{
    models::Friend* _friend = new models::Friend(payload._friend);
    models::Friend* existFriend = implementation->userController->getFriendByName(_friend->friendName->value());
    if (existFriend == nullptr)
    {
        implementation->userController->addFriend(_friend);
        implementation->viewController->friendListViewModel->onFriendAdded(_friend);
    }
    else
    {
        existFriend->friendIp->setValue(_friend->friendIp->value());
        existFriend->status->setValue(_friend->status->value());
        implementation->viewController->friendListViewModel->onFriendChanged(_friend);
    }
}

void ServiceController::NET_onMessageReceivedExecuted(models::PayloadModel& payload) //Incoming
{
    models::Message* newMessage = new models::Message(payload.message);

    QString friendReference = newMessage->sender->value();
    implementation->userController->addMessage(friendReference, newMessage);
    implementation->viewController->chatDetailViewModel->onMessagesAdded(newMessage);
}

void ServiceController::MS_onMessageSendSignal(models::Message &message)
{
    QJsonObject& send_task = implementation->taskFormerService->formMessageSendTask(message);
    implementation->taskExecutorBinder->sendNetTask(send_task);
}

/*
void ServiceController::MS_onCommonFriendListRequestedSignal(QString &friendName)
{

}
*/

void ServiceController::MS_onMessageStatusRequestedSignal(QString friendName, QString messageReference)
{
    models::Message* message = implementation->userController->getMessageByFriend(friendName, messageReference);
    if (message != nullptr)
    {
        emit MS_sendMessageStatus(messageReference, static_cast<models::Message::eMessageStatus>(message->messageStatus->value()));
    }
}

void ServiceController::MS_onFriendStatusRequestedSignal(QString& friendName)
{
    models::Friend* _friend = implementation->userController->getFriendByName(friendName);
    if (_friend != nullptr)
    {
        emit MS_sendFriendStatus(friendName, static_cast<models::Friend::eStatus>(_friend->status->value()));
    }
}


}
}

