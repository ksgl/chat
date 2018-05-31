#include "task-former-service.h"

namespace chat {
namespace services {

QJsonObject& TaskFormerService::TaskFormerService(QObject *parent) : QObject(parent)
{
}

QJsonObject& TaskFormerService::formLoginTask(QString &login, QString &password)
{
    models::NetCommandModel* send_command = new models::NetCommandModel(this);
    send_command->command_type->setValue("user.login");
    send_command->payload->loginData->login->setValue(login);
    send_command->payload->loginData->password->setValue(password);

    return send_command->toJson();
}

QJsonObject& TaskFormerService::formRegisterTask(QString &login, QString &password)
{
    models::NetCommandModel* send_command = new models::NetCommandModel(this);
    send_command->command_type->setValue("user.register");
    send_command->payload->loginData->login->setValue(login);
    send_command->payload->loginData->password->setValue(password);

    return send_command->toJson();
}

QJsonObject& TaskFormerService::formFriendRequestTask(QString &friendName)
{
    models::NetCommandModel* send_command = new models::NetCommandModel(this);
    send_command->command_type->setValue("user.add_friend");
    send_command->payload->_friend->friendName->setValue(friendName);

    return send_command->toJson();
}

QJsonObject& TaskFormerService::formMessageSendTask(models::Message &message)
{
    models::NetCommandModel* send_command = new models::NetCommandModel(this);
    send_command->command_type->setValue("user.message_send");
    send_command->payload->message->update(message.toJson());

    return send_command->toJson();
}


}
}

