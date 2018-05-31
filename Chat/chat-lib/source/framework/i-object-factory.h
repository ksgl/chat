#ifndef IOBJECTFACTORY_H
#define IOBJECTFACTORY_H

#include <task-exec/TaskExecutor.hpp>

#include <controllers/i-navigation-controller.h>
#include <controllers/i-command-controller.h>
#include <controllers/view-controller.h>
#include <controllers/service-controller.h>
#include <controllers/i-user-controller.h>
#include <services/task-executor-callback-binder.h>

namespace chat {
namespace framework {

class IObjectFactory
{
public:
    virtual ~IObjectFactory(){}

    virtual controllers::INavigationController* createNavigationController(QObject* parent) const = 0;
    virtual controllers::ICommandController* createCommandController(QObject* parent, controllers::INavigationController* navigationController) const = 0;
    virtual controllers::ViewController* createViewController(QObject* parent) const = 0;
    virtual controllers::IUserController* createUserController(QObject* parent, models::UserModel* user) const = 0;
    virtual services::TaskExecutorCallbackBinder* createTaskExecutorCallbackBinder(QObject* parent, TaskExecuterRunner* task_exec) const = 0;
    virtual controllers::ServiceController* createServiceController(QObject* parent, controllers::ICommandController* commandController,
                                                                    services::TaskExecutorCallbackBinder* taskExecotorCallbackBinder,
                                                                    controllers::IUserController* userController,
                                                                    controllers::ViewController* viewController) const = 0;
};

}

}
#endif // IOBJECTFACTORY_H
