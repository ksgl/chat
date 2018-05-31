#ifndef FRIENDLISTVIEWMODEL_H
#define FRIENDLISTVIEWMODEL_H

#include <QObject>
#include <QtQml/QQmlListProperty>

#include <chat-lib_global.h>
#include <models/friend.h>

namespace chat {
namespace views {

class CHATLIBSHARED_EXPORT FriendListViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<chat::models::Friend> ui_friends READ ui_friends NOTIFY friendsChanged )

public:
    FriendListViewModel(QObject* parent = nullptr);

    QQmlListProperty<chat::models::Friend> ui_friends();
    QList<chat::models::Friend*> friends;

signals:
    void friendAddedToView();
    void friendsChanged();

    //conected to ServiceController
    void gui_chatDetailViewRequested(QString friendReference);

public slots:
    void onFriendAdded(models::Friend* newFriend);
    void onFriendChanged(models::Friend* _friend);
    void SetFriends(QList<chat::models::Friend*> friends);
    bool isEmpty(){ return friends.isEmpty();}
};


}
}


#endif // FRIENDLISTVIEWMODEL_H
