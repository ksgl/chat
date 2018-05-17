#ifndef TASKEXECUTORCALLBACKBINDER_H
#define TASKEXECUTORCALLBACKBINDER_H

#include <QObject>

#include <chat-lib_global.h>
#include <services/i-task-executor-callback-binder.h>
#include <framework/callback.h>

namespace chat {
namespace services {

class CHATLIBSHARED_EXPORT TaskExecutorCallbackBinder : public QObject, ITaskExecutorCallbackBinder
{
    Q_OBJECT
public:
    explicit TaskExecutorCallbackBinder(QObject *parent = nullptr);
    ~TaskExecutorCallbackBinder();

    std::vector<std::pair<std::string*, framework::CallbackPtr<ITaskExecutorCallbackBinder, int>>> callbacks();

    int LoginAnswerReceivedBinder(std::string* data);
    int RegistrationAnswerReceivedBinder(std::string* data);
    int FriendReceivedBinder(std::string* data);
    int MessageReceivedBinder(std::string* data);

signals:

    void LoginAnswerReceived(QString data);
    void RegisterAnswerReceived(QString data);
    void MessageReceived(QString data);
    void FriendReceived(QString data);

public slots:

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;

};



}
}


#endif // TASKEXECUTORCALLBACKBINDER_H
