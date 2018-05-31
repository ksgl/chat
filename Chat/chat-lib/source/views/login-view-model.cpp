#include "login-view-model.h"

#include <QDebug>

namespace chat {
namespace views {

LoginViewModel::LoginViewModel(QObject *parent)
    : QObject(parent),
      state(NotAuthorized),
      login(""),
      password("")
{
}

void LoginViewModel::onLoginButtonClicked()
{
    if (!login.isEmpty() && !password.isEmpty())
    {
        state = WaitingForServerAnswer;
        emit changeState(static_cast<int>(state));
        emit LoginReceived(login, password);
    }
}

void LoginViewModel::onLoginErrorReceived()
{
    state = Error_OtherError;
    emit changeState(static_cast<int>(state));
}

void LoginViewModel::onLoginSuccessReceived()
{
    state = SuccessfulAuthorization;
    emit changeState(static_cast<int>(state));
}

}}
