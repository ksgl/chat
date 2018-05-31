#ifndef VIEWCONTROLLER_H
#define VIEWCONTROLLER_H

#include <QObject>

#include <chat-lib_global.h>
#include <views/login-view-model.h>
#include <views/registration-view-model.h>
#include <views/chat-list-model-view.h>
#include <views/chat-detail-view-model.h>
#include <views/friend-list-view-model.h>

namespace chat {
namespace controllers {

class CHATLIBSHARED_EXPORT ViewController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(chat::views::LoginViewModel* ui_loginViewModel MEMBER loginViewModel NOTIFY loginViewChanged)
    Q_PROPERTY(chat::views::RegistrationViewModel* ui_registrationViewModel MEMBER registrationViewModel NOTIFY registrationViewModelChanged)
    Q_PROPERTY(chat::views::ChatListModelView* ui_chatListModelView MEMBER chatListModelView NOTIFY chatListViewModelChanged)
    Q_PROPERTY(chat::views::ChatDetailViewModel* ui_chatDetailViewModel MEMBER chatDetailViewModel NOTIFY chatDetailViewModelChanged)
    Q_PROPERTY(chat::views::FriendListViewModel* ui_friendListViewModel MEMBER friendListViewModel NOTIFY friendListViewChanged)

public:
    ViewController(QObject* _parent = nullptr);
    ~ViewController();

    views::LoginViewModel* loginViewModel{nullptr};
    views::RegistrationViewModel* registrationViewModel{nullptr};
    views::ChatListModelView* chatListModelView{nullptr};
    views::ChatDetailViewModel* chatDetailViewModel{nullptr};
    views::FriendListViewModel* friendListViewModel{nullptr};

signals:
    void loginViewChanged();
    void registrationViewModelChanged();
    void chatListViewModelChanged();
    void chatDetailViewModelChanged();
    void friendListViewChanged();
};


}
}


#endif // VIEWCONTROLLER_H
