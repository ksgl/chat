#include "chat-list-model-view.h"

using namespace chat::models;
namespace chat {
namespace views {

ChatListModelView::ChatListModelView(QObject* parent)
    : QObject(parent)
{
}

QQmlListProperty<chat::models::ChatModel> ChatListModelView::ui_chats()
{
    return QQmlListProperty<ChatModel>(this, chats);
}

void ChatListModelView::SetChats(QList<ChatModel*> _chats)
{
    chats = _chats;
}

void ChatListModelView::onChatAdded(models::ChatModel* newChat)
{
    chats.append(newChat);
    emit chatAddedToView();
}



}
}
