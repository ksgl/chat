#ifndef REGISTRATIONVIEWMODEL_H
#define REGISTRATIONVIEWMODEL_H


#include <QObject>

#include <chat-lib_global.h>

namespace chat {
namespace views {

class CHATLIBSHARED_EXPORT RegistrationViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString ui_login MEMBER login NOTIFY changed)
    Q_PROPERTY(QString ui_password MEMBER password NOTIFY changed)
    Q_PROPERTY(int ui_state MEMBER state NOTIFY changeState(ui_state))

public:
    explicit RegistrationViewModel(QObject *parent = nullptr);

    QString login;
    QString password;

    enum RegistrationAuthenticationStates
    {
        NotAuthorized = 0,
        WaitingForServerAnswer,
        Error_UserExists,
        Error_OtherError,
        SuccessfulAuthorization
    };

    int state;

signals:

    // логин на подтверждение
    void RegistrationReceived(QString& login, QString& password);

    // отправка статуса процесса на GUI
    void changeState(int state);
    void changed();

public slots:
    // сигнал от GUI
    void onRegisterButtonClicked();

    // сигналы со стороны проверки
    void onRegisterErrorReceived();
    void onRegisterUserExistsErrorReceived();
    void onRegisterSuccessReceived();
};

}}

#endif // REGISTRATIONVIEWMODEL_H
