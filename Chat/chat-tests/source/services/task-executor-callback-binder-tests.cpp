#include "task-executor-callback-binder-tests.h"

using namespace std;

namespace chat {
namespace services {

static TaskExecutorCallbackBinderTests instance;

TaskExecutorCallbackBinderTests::TaskExecutorCallbackBinderTests()
    : TestSuite( "TaskExecutorCallbackBinderTests" )
{
}

}

namespace services { // Scaffolding

void TaskExecutorCallbackBinderTests::initTestCase()
{
}

void TaskExecutorCallbackBinderTests::cleanupTestCase()
{
}

void TaskExecutorCallbackBinderTests::init()
{
    taskExecutorCallbackBinder = new TaskExecutorCallbackBinder(this);
}

void TaskExecutorCallbackBinderTests::cleanup()
{
    if (taskExecutorCallbackBinder != nullptr)
    {
        taskExecutorCallbackBinder->deleteLater();
        taskExecutorCallbackBinder = nullptr;
    }
}
}

namespace services {

void TaskExecutorCallbackBinderTests::callbacks_returnsCallbackList()
{
    vector<pair<string*, framework::CallbackPtr<ITaskExecutorCallbackBinder, int>>> callbacks;
    callbacks = taskExecutorCallbackBinder->callbacks();

    QCOMPARE (callbacks.size(), 4);
    QCOMPARE (callbacks.at(0).first->c_str(), "LoginAnswerRecieved");
}

void TaskExecutorCallbackBinderTests::executeCallback_emitsSignal()
{
    vector<pair<string*, framework::CallbackPtr<ITaskExecutorCallbackBinder, int>>> callbacks;
    callbacks = taskExecutorCallbackBinder->callbacks();

    QSignalSpy signalEmitsSpy(taskExecutorCallbackBinder, &TaskExecutorCallbackBinder::LoginAnswerReceived);

    std::string* message = new string("Hello!");
    int result = callbacks.at(0).second.callback(message);
    QCOMPARE( result, 0);
    QCOMPARE( signalEmitsSpy.count(), 1);
    QCOMPARE( signalEmitsSpy.takeFirst().takeFirst(), QString(message->c_str()));
}

}
}


