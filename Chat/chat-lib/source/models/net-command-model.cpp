#include "net-command-model.h"

using namespace chat::data;

namespace chat {
namespace models {

LoginModel::LoginModel(QObject *parent)
    : Entity(parent, "loginData")
{
    login = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "login", "login")));
    password = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "password", "password")));
    loginStatus = static_cast<IntDecorator*>(addDataItem(new StringDecorator(this, "loginStatus", "Login Status")));
}

LoginModel::LoginModel(QObject *parent, const QJsonObject &json)
{
    update(json);
}

PayloadModel::PayloadModel(QObject *parent)
    : Entity(parent, "payload")
{
    message = static_cast<Message*>(addChild(new Message(this), "message"));
    _friend = static_cast<Friend*>(addChild(new Friend(this), "friend"));
    loginData = static_cast<LoginModel*>(addChild(new LoginModel(this), "loginData"));
}

PayloadModel::PayloadModel(QObject *parent, const QJsonObject &json)
    : PayloadModel(parent)
{
    update(json);
}

NetCommandModel::NetCommandModel(QObject* parent)
    : Entity(parent, "net_command")
{
    command_type = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "command", "command")));
    payload = static_cast<PayloadModel*>(addChild(new PayloadModel(this), "payload"));
}

NetCommandModel::NetCommandModel(QObject *parent, const QJsonObject &json)
    : NetCommandModel(parent)
{
    update(json);
}

}
}

