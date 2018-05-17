#ifndef TASKEXECUTORCALLBACKBINDERTESTS_H
#define TASKEXECUTORCALLBACKBINDERTESTS_H

#include <QtTest>

#include <test-suite.h>
#include <services/task-executor-callback-binder.h>

namespace chat {
namespace services {

class TaskExecutorCallbackBinderTests : public TestSuite
{
    Q_OBJECT

public:
    TaskExecutorCallbackBinderTests();

private slots:

    /// @brief Called before the first test function is executed
    void initTestCase();
    /// @brief Called after the last test function was executed.
    void cleanupTestCase();
    /// @brief Called before each test function is executed.
    void init();
    /// @brief Called after every test function.
    void cleanup();

private slots:
    void callbacks_returnsCallbackList();
    void executeCallback_emitsSignal();

private:
    TaskExecutorCallbackBinder* taskExecutorCallbackBinder{nullptr};

};

}
}


#endif // TASKEXECUTORCALLBACKBINDERTESTS_H
