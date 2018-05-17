#include "service-controller.h"

using namespace chat::services;

namespace chat {
namespace controllers {

class ServiceController::Implementation
{
public:
    Implementation(ServiceController* _serviceController,
                   ICommandController* _commandController,
                   TaskExecutorCallbackBinder* _taskExecutorBinder,
                   IUserController* _userController)
        : serviceController(_serviceController),
          commandController(_commandController),
          taskExecutorBinder(_taskExecutorBinder),
          userController(_userController)
    {
        QObject::connect( commandController, &ICommandController::LoginCommandExecuted, serviceController, &ServiceController::onLoginCommandExecuted);
        QObject::connect( commandController, &ICommandController::RegisterCommandExecuted, serviceController, &ServiceController::onRegisterCommandExecuted);
        QObject::connect( commandController, &ICommandController::AddChatCommandExecuted, serviceController, &ServiceController::onAddChatCommandExecuted);
        QObject::connect( commandController, &ICommandController::FindNewFriendCommandExecuted, serviceController, &ServiceController::onFindNewFriendCommandExecuted);
        QObject::connect( commandController, &ICommandController::SendMessageCommandExecuted, serviceController, &ServiceController::onSendMessageCommandExecuted);
        QObject::connect( commandController, &ICommandController::ExitCommandExecuted, serviceController, &ServiceController::onExitCommandExecuted);

        QObject::connect( taskExecutorBinder, &TaskExecutorCallbackBinder::LoginAnswerReceived, serviceController, &ServiceController::onLoginAnswerReceivedExecuted);
        QObject::connect( taskExecutorBinder, &TaskExecutorCallbackBinder::RegisterAnswerReceived, serviceController, &ServiceController::onLoginAnswerReceivedExecuted);
        QObject::connect( taskExecutorBinder, &TaskExecutorCallbackBinder::FriendReceived, serviceController, &ServiceController::onFriendReceiverExecuted);
        QObject::connect( taskExecutorBinder, &TaskExecutorCallbackBinder::MessageReceived, serviceController, &ServiceController::onMessageReceivedExecuted);
    }

    ServiceController* serviceController{nullptr};
    ICommandController* commandController{nullptr};
    TaskExecutorCallbackBinder* taskExecutorBinder{nullptr};
    IUserController* userController{nullptr};
};

ServiceController::ServiceController(QObject *parent, ICommandController* _commandController, TaskExecutorCallbackBinder* _taskExecutorBinder,
                                     IUserController* _userController)
    : QObject(parent)
{
    implementation.reset(new Implementation(this, _commandController, _taskExecutorBinder, _userController));
}

ServiceController::~ServiceController()
{
    QObject::disconnect( implementation->commandController, &ICommandController::LoginCommandExecuted, implementation->serviceController, &ServiceController::onLoginCommandExecuted);
    QObject::disconnect( implementation->commandController, &ICommandController::RegisterCommandExecuted, implementation->serviceController, &ServiceController::onRegisterCommandExecuted);
    QObject::disconnect( implementation->commandController, &ICommandController::AddChatCommandExecuted, implementation->serviceController, &ServiceController::onAddChatCommandExecuted);
    QObject::disconnect( implementation->commandController, &ICommandController::FindNewFriendCommandExecuted, implementation->serviceController, &ServiceController::onFindNewFriendCommandExecuted);
    QObject::disconnect( implementation->commandController, &ICommandController::SendMessageCommandExecuted, implementation->serviceController, &ServiceController::onSendMessageCommandExecuted);
    QObject::disconnect( implementation->commandController, &ICommandController::ExitCommandExecuted, implementation->serviceController, &ServiceController::onExitCommandExecuted);

    QObject::disconnect( implementation->taskExecutorBinder, &TaskExecutorCallbackBinder::LoginAnswerReceived, implementation->serviceController, &ServiceController::onLoginAnswerReceivedExecuted);
    QObject::disconnect( implementation->taskExecutorBinder, &TaskExecutorCallbackBinder::RegisterAnswerReceived, implementation->serviceController, &ServiceController::onLoginAnswerReceivedExecuted);
    QObject::disconnect( implementation->taskExecutorBinder, &TaskExecutorCallbackBinder::FriendReceived, implementation->serviceController, &ServiceController::onFriendReceiverExecuted);
    QObject::disconnect( implementation->taskExecutorBinder, &TaskExecutorCallbackBinder::MessageReceived, implementation->serviceController, &ServiceController::onMessageReceivedExecuted);
}

void ServiceController::onLoginCommandExecuted(QString data)
{
    /*
    QJsonObject netTask = implementation->taskFormerService->formLoginTask(data);
    implementation->taskHandlerSenderService->sendNetTask( netTask );
    */
}

void ServiceController::onRegisterCommandExecuted(QString data)
{
    /*
    QJsonObject netTask = implementation->taskFormerService->formRegisterTask( data );
    implementation->taskHandlerSenderService->sendNetTask( netTask );
    */
}

void ServiceController::onAddChatCommandExecuted(QString data)
{
    //QString friendReference = implementation->rawStringParser->parseFriendReference(data);
    models::Friend* _friend = implementation->userController->getFriend(data);
    if (_friend  != nullptr)
    {
        //implementation->userController->addChat(_friend);
    }
    else
    {
        //Process FriendNotFound
    }
}

void ServiceController::onSendMessageCommandExecuted(QString data) //Data + Receiver
{
    /*
    //Проверка правильности ресивера
    models::Message* message = implementation->rawStringParser->parseNewMessage(data);

    message->sender->setValue(implementation->userController->userReference());
    message->sendAt->setValue(QDateTime::currentDateTime());
    message->messageType->setValue(models::Message::eMessageType::Outgoing);
    message->messageStatus->setValue(models::Message::eMessageStatus::NotDelivered);

    implementation->userController->addMessage(message->receiver->value(), message);

    models::Friend::eStatus currStatus = implementation->userController->getFriendStatus(message->receiver->value());
    if (currStatus == models::Friend::eStatus::Online)
    {
        QJsonObject netTask = taskFormerService->formSendMessageTask(data);
        taskHandlerSenderService->sendNetTask( netTask );
    }
    */
}

void ServiceController::onFindNewFriendCommandExecuted(QString data)
{
    /*
    QJsonObject netTask = taskFormerService->formFriendRequestedTask(data);
    taskHandlerSenderService->sendNetTask( netTask );
    */
}

void ServiceController::onExitCommandExecuted()
{
    /*
    QJsonObject netTask = taskFormerService->formExitTask(data);
    taskHandlerSenderService->sendNetTask( netTask );
    */
}

void ServiceController::onLoginAnswerReceivedExecuted(QString data)
{
    /*
    int loginResult = implementation->rawStringParser->parseLoginAnswer(data);
    if (loginResult == 0)
    {
        implementation->commandController->onChatListViewExecuted();
    }
    */
}

void ServiceController::onRegisterAnswerReceivedExecuted(QString data)
{
    /*
    int registerResult = implementation->rawStringParser->parseRegisterAnswer(data);
    if (registerResult == 0)
    {
        implementation->commandController->onChatListViewExecuted();
    }
    else if (registerResult == 1)
    {
        //LOGIN EXISTS
    }
    else
    {
        //OTHER ERROR
    }
    */
}

void ServiceController::onFriendReceiverExecuted(QString data) //Name + Ip + Status
{
    /*
    models::Friend* _friend = implementation->rawStringParser->parseFriendAnswer(data);
    models::Friend* existFriend = implementation->userController->getFriendByName(_friend->friendName->value());
    if (existFriend == nullptr)
    {
        implementation->userController->addFriend(_friend);
    }
    else
    {
        existFriend->friendIp->setValue(_friend->friendIp->value());
        existFriend->status->setValue(_friend->status->value());
    }
    */
}

void ServiceController::onMessageReceivedExecuted(QString data) //Incoming
{
    /*
    models::Message* message = implementation->rawStringParser->parseReceivedMessage(data);
    QString friendReference = message->sender->value();
    implementation->userController->addMessage(friendReference, message);
    */
}

}
}

