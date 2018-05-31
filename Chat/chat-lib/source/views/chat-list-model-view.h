#ifndef CHATLISTMODELVIEW_H
#define CHATLISTMODELVIEW_H

#include <QObject>
#include <QtQml/QQmlListProperty>

#include <chat-lib_global.h>
#include <models/chat-model.h>

namespace chat {
namespace views {

class CHATLIBSHARED_EXPORT ChatListModelView : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<chat::models::ChatModel> ui_chats READ  ui_chats NOTIFY chatChanged)

public:
    ChatListModelView(QObject* parent = nullptr);

    QQmlListProperty<chat::models::ChatModel> ui_chats();
    QList<chat::models::ChatModel*> chats;

signals:
    void chatAddedToView();
    void chatChanged();

    //conected to ServiceController
    void gui_chatDetailViewRequested(QString friendReference);

public slots:
    void onChatAdded(models::ChatModel* newChat);
    void SetChats(QList<chat::models::ChatModel*> chats);
    bool isEmpty() { return chats.isEmpty(); }
};


}
}


#endif // CHATLISTMODELVIEW_H
