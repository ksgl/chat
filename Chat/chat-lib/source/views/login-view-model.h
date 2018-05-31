#ifndef LOGINVIEWMODEL_H
#define LOGINVIEWMODEL_H

#include <QObject>

#include <chat-lib_global.h>

namespace chat {
namespace views {

class CHATLIBSHARED_EXPORT LoginViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString ui_login MEMBER login NOTIFY changed)
    Q_PROPERTY(QString ui_password MEMBER password NOTIFY changed)
    Q_PROPERTY(int ui_state MEMBER state NOTIFY changeState(ui_state))

public:
    explicit LoginViewModel(QObject *parent = nullptr);

    QString login;
    QString password;

    enum LoginAuthenticationStates
    {
        NotAuthorized = 0,
        WaitingForServerAnswer,
        Error_OtherError,
        SuccessfulAuthorization
    };

    int state;

signals:

    // логин на подтверждение
    void LoginReceived(QString& login, QString& password);

    void changeState(int state);
    void changed();

public slots:
    // сигнал от GUI
    void onLoginButtonClicked();

    // сигнал от подтвеждения
    void onLoginErrorReceived();
    void onLoginSuccessReceived();
};

}}

#endif // LOGINVIEWMODEL_H
