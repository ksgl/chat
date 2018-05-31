#ifndef INAVIGATIONCONTROLLER_H
#define INAVIGATIONCONTROLLER_H

#include <QObject>

#include <chat-lib_global.h>
#include <models/chat-model.h>

namespace chat {
namespace controllers {

class CHATLIBSHARED_EXPORT INavigationController : public QObject
{
    Q_OBJECT

public:
    INavigationController(QObject* parent) : QObject(parent){}
    virtual ~INavigationController(){}

signals:
    void goExitView();
    void goLoginView();
    void goRegistrationView();
    void goChatListView();
    void goChatView();
    void goFriendListView();
    void goAddFriendView();
    void goMainView();
    void goRequestsFriendsView();
    void goResponcesFriendsView();
};

}
}
#endif // INAVIGATIONCONTROLLER_H
