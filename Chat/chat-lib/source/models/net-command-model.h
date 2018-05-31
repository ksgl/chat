#ifndef NETCOMMANDMODEL_H
#define NETCOMMANDMODEL_H

#include <QObject>
#include <QtQml/QQmlListProperty>

#include <chat-lib_global.h>
#include <data/string-decorator.h>
#include <data/int-decorator.h>
#include <models/message.h>
#include <models/friend.h>

namespace chat {
namespace models {


class CHATLIBSHARED_EXPORT LoginModel : public data::Entity
{
    Q_OBJECT

public:
    LoginModel(QObject* parent = nullptr);
    LoginModel(QObject* parent, const QJsonObject& json);

    data::StringDecorator* login{nullptr};
    data::StringDecorator* password{nullptr};
    data::IntDecorator* loginStatus{nullptr}; // 0 - ok, 1 - error, 2 - user already exists

};

class CHATLIBSHARED_EXPORT PayloadModel : public data::Entity
{
    Q_OBJECT

public:
    PayloadModel(QObject* parent = nullptr);
    PayloadModel(QObject* parent, const QJsonObject& json);

    models::Message* message{nullptr};
    models::Friend* _friend{nullptr};
    models::LoginModel* loginData{nullptr};

};

class CHATLIBSHARED_EXPORT NetCommandModel : public data::Entity
{
    Q_OBJECT

public:
    NetCommandModel(QObject* parent = nullptr);
    NetCommandModel(QObject* parent, const QJsonObject& json);

    data::StringDecorator* command_type{nullptr};
    models::PayloadModel* payload{nullptr};

};

}
}


#endif // NETCOMMANDMODEL_H
