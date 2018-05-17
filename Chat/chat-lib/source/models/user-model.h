#ifndef USERMODEL_H
#define USERMODEL_H

#include <QObject>
#include <QtQml/QQmlListProperty>

#include <chat-lib_global.h>

#include <data/string-decorator.h>
#include <data/entity.h>
#include <data/entity-collection.h>
#include <models/friend.h>
#include <models/chat-model.h>

namespace chat {
namespace models {

class CHATLIBSHARED_EXPORT UserModel : public data::Entity
{
    Q_OBJECT
    Q_PROPERTY(chat::data::StringDecorator* ui_reference MEMBER reference CONSTANT)
    Q_PROPERTY(chat::data::StringDecorator* ui_name MEMBER name CONSTANT)
    Q_PROPERTY( QQmlListProperty<chat::models::Friend> ui_friends READ ui_friends NOTIFY friendsChanged )
    Q_PROPERTY( QQmlListProperty<chat::models::ChatModel> ui_chats READ ui_chats NOTIFY chatsChanged )

public:
    explicit UserModel(QObject* parent = nullptr);
    UserModel(QObject *parent, const QJsonObject& json);

    data::StringDecorator* reference{nullptr};
    data::StringDecorator* name{nullptr};
    data::StringDecorator* publicKey{nullptr};

    data::EntityCollection<Friend>* friends{nullptr};
    data::EntityCollection<ChatModel>* chats{nullptr};

    QQmlListProperty<chat::models::Friend> ui_friends();
    QQmlListProperty<chat::models::ChatModel> ui_chats();


signals:
    void friendsChanged();
    void chatsChanged();
};


}
}


#endif // USERMODEL_H
