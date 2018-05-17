#ifndef ITASKEXECUTORCALLBACKBINDER_H
#define ITASKEXECUTORCALLBACKBINDER_H

#include <QObject>

#include <chat-lib_global.h>
#include <framework/callback.h>

namespace chat {
namespace services {

class CHATLIBSHARED_EXPORT ITaskExecutorCallbackBinder
{

public:
    virtual ~ITaskExecutorCallbackBinder(){}

    virtual std::vector<std::pair<std::string*, framework::CallbackPtr<ITaskExecutorCallbackBinder, int>>> callbacks() = 0;

    virtual int LoginAnswerReceivedBinder(std::string* data) = 0;
    virtual int RegistrationAnswerReceivedBinder(std::string* data) = 0;
    virtual int FriendReceivedBinder(std::string* data) = 0;
    virtual int MessageReceivedBinder(std::string* data) = 0;

};



}
}

#endif // ITASKEXECUTORCALLBACKBINDER_H
