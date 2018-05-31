#ifndef MOCKOBJECTFACTORY_H
#define MOCKOBJECTFACTORY_H

#include <framework/i-object-factory.h>

namespace chat {
namespace framework {

class MockObjectFactory : public IObjectFactory
{
public:
    MockObjectFactory(){}

    //controllers::IDatabaseController* createDatabaseController(QObject* parent) const override { return nullptr; }
    controllers::INavigationController* createNavigationController(QObject* parent) const override { return nullptr; }
    controllers::ICommandController* createCommandController(QObject* parent, /*controllers::IDatabaseController* databaseController,*/ controllers::INavigationController* navigationController) const override { return nullptr; }
    controllers::ViewController* createViewController(QObject *parent) const override { return nullptr;  }
    controllers::IUserController* createUserController(QObject* parent, models::UserModel* user, bool is_User_1) const override {return nullptr;}
    services::TaskExecutorCallbackBinder* createTaskExecutorCallbackBinder(QObject* parent) const override {return nullptr;}
    controllers::ServiceController* createServiceController(QObject* parent, controllers::ICommandController* commandController,
                                                                    services::TaskExecutorCallbackBinder* taskExecotorCallbackBinder,
                                                                    controllers::IUserController* userController, controllers::ViewController* viewController) const override {return nullptr;}

};

}}

#endif
