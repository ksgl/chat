#include "task-executor-callback-binder.h"

#define INTMETHOD(m) CALLBACK(int, chat::services::ITaskExecutorCallbackBinder, m)

using namespace chat::framework;
using namespace std;

namespace chat {
namespace services {

typedef pair<string*, CallbackPtr<ITaskExecutorCallbackBinder, int>> NameCallbackPair;

class TaskExecutorCallbackBinder::Implementation
{
public:
    Implementation(ITaskExecutorCallbackBinder* _taskExecutorCallbackBinder)
        : taskCallbackBinder(_taskExecutorCallbackBinder)
    {
        CallbackPtr<ITaskExecutorCallbackBinder, int> LoginReceivedCallback (taskCallbackBinder, INTMETHOD(LoginAnswerReceivedBinder));
        string* CLoginName = new string("LoginAnswerRecieved");
        NameCallbackPair LoginReceivedCallbackPair(CLoginName, LoginReceivedCallback);
        callbacks.push_back(LoginReceivedCallbackPair);

        CallbackPtr<ITaskExecutorCallbackBinder, int> RegistrationReceivedCallback (taskCallbackBinder, INTMETHOD(RegistrationAnswerReceivedBinder));
        string* CRegName = new string("RegistrationAnswerRecieved");
        NameCallbackPair RegistrationReceivedCallbackPair(CRegName, RegistrationReceivedCallback);
        callbacks.push_back(RegistrationReceivedCallbackPair);

        CallbackPtr<ITaskExecutorCallbackBinder, int> FriendReceivedCallback (taskCallbackBinder, INTMETHOD(FriendReceivedBinder));
        string* CFrName = new string("FriendRecieved");
        NameCallbackPair FriendReceivedCallbackPair(CFrName, FriendReceivedCallback);
        callbacks.push_back(FriendReceivedCallbackPair);

        CallbackPtr<ITaskExecutorCallbackBinder, int> MessageReceivedCallback (taskCallbackBinder, INTMETHOD(MessageReceivedBinder));
        string* CMsName = new string("MessageRecieved");
        NameCallbackPair MessageReceivedCallbackPair(CMsName, MessageReceivedCallback);
        callbacks.push_back(MessageReceivedCallbackPair);

    }

    ITaskExecutorCallbackBinder* taskCallbackBinder{nullptr};
    vector<NameCallbackPair> callbacks{};
};

TaskExecutorCallbackBinder::TaskExecutorCallbackBinder(QObject *parent) : QObject(parent)
{
    implementation.reset(new Implementation(this));
}

TaskExecutorCallbackBinder::~TaskExecutorCallbackBinder(){}

vector<NameCallbackPair> TaskExecutorCallbackBinder::callbacks()
{
    return implementation->callbacks;
}

int TaskExecutorCallbackBinder::LoginAnswerReceivedBinder(string* data)
{
    QString qdata(data->c_str());
    emit LoginAnswerReceived(qdata);
    return 0;
}

int TaskExecutorCallbackBinder::RegistrationAnswerReceivedBinder(string* data)
{
    QString qdata(data->c_str());
    emit RegisterAnswerReceived(qdata);
    return 0;
}

int TaskExecutorCallbackBinder::FriendReceivedBinder(string* data)
{
    QString qdata(data->c_str());
    emit FriendReceived(qdata);
    return 0;
}

int TaskExecutorCallbackBinder::MessageReceivedBinder(string* data)
{
    QString qdata(data->c_str());
    emit MessageReceived(qdata);
    return 0;
}

}
}

