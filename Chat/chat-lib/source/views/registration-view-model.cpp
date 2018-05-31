#include "registration-view-model.h"

#include <QDebug>

namespace chat {
namespace views {

RegistrationViewModel::RegistrationViewModel(QObject *parent)
    : QObject(parent),
      state(NotAuthorized),
      login(""),
      password("")
{
}

void RegistrationViewModel::onRegisterButtonClicked()
{
    if (!login.isEmpty() && !password.isEmpty())
    {
        state = WaitingForServerAnswer;
        emit changeState(static_cast<int>(state));
        emit RegistrationReceived(login, password);
    }
}

void RegistrationViewModel::onRegisterErrorReceived()
{
    state = Error_OtherError;
    emit changeState(static_cast<int>(state));
}

void RegistrationViewModel::onRegisterUserExistsErrorReceived()
{
    state = Error_OtherError;
    emit changeState(static_cast<int>(state));
}

void RegistrationViewModel::onRegisterSuccessReceived()
{
    state = SuccessfulAuthorization;
    emit changeState(static_cast<int>(state));
}

}}

