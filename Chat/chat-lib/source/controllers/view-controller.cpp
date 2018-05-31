#include "view-controller.h"

using namespace chat::views;

namespace chat {
namespace controllers {

ViewController::ViewController(QObject* _parent)
    : QObject(_parent)
{
    loginViewModel = new LoginViewModel(this);
    registrationViewModel = new RegistrationViewModel(this);
    chatListModelView = new ChatListModelView(this);
    chatDetailViewModel = new ChatDetailViewModel(this);
    friendListViewModel = new FriendListViewModel(this);
}

ViewController::~ViewController()
{
}

}
}

