#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include <framework/i-object-factory.h>

namespace chat {
namespace framework {

class CHATLIBSHARED_EXPORT ObjectFactory : public IObjectFactory
{
public:
    ObjectFactory();

    controllers::INavigationController* createNavigationController(QObject* parent) const override;
    controllers::ICommandController* createCommandController(QObject *parent, controllers::INavigationController *navigationController) const override;
    controllers::ViewController* createViewController(QObject *parent) const override;
    controllers::IUserController* createUserController(QObject* parent, models::UserModel* user) const;
    services::TaskExecutorCallbackBinder* createTaskExecutorCallbackBinder(QObject* parent, TaskExecuterRunner* task_exec) const;
    controllers::ServiceController* createServiceController(QObject* parent, controllers::ICommandController* commandController,
                                                                    services::TaskExecutorCallbackBinder* taskExecotorCallbackBinder,
                                                                    controllers::IUserController* userController, controllers::ViewController* viewController) const;

};

}
}

#endif // OBJECTFACTORY_H
