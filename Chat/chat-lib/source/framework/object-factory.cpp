#include "object-factory.h"

#include <controllers/navigation-controller.h>
#include <controllers/command-controller.h>
#include <controllers/user-controller.h>

using namespace chat::controllers;

namespace chat {
namespace framework {

ObjectFactory::ObjectFactory() : IObjectFactory() {}

INavigationController* ObjectFactory::createNavigationController(QObject *parent) const
{
    return new NavigationController(parent);
}

ICommandController* ObjectFactory::createCommandController(QObject* parent, INavigationController* navigationController) const
{
    return new CommandController(parent, navigationController);
}

ViewController* ObjectFactory::createViewController(QObject *parent) const
{
    return new ViewController(parent);
}

IUserController* ObjectFactory::createUserController(QObject* parent, models::UserModel* user) const
{
    return new UserController(parent, user);
}

services::TaskExecutorCallbackBinder* ObjectFactory::createTaskExecutorCallbackBinder(QObject* parent, TaskExecuterRunner* task_exec) const
{
    return new services::TaskExecutorCallbackBinder(parent);
}

ServiceController* ObjectFactory::createServiceController(QObject* parent, controllers::ICommandController* commandController,
                                                          services::TaskExecutorCallbackBinder* taskExecotorCallbackBinder,
                                                          controllers::IUserController* userController,
                                                          controllers::ViewController* viewController) const
{
    return new ServiceController(parent, commandController, taskExecotorCallbackBinder, userController, viewController);
}


}
}
