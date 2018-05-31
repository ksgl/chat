#include "master-controller.h"

using namespace chat::framework;

namespace chat {
namespace controllers {

class MasterController::Implementation {

public:
    Implementation(MasterController* _masterController, IObjectFactory* _objectFactory, TaskExecuterRunner* _task_exec)
        : masterController(_masterController),
          objectFactory(_objectFactory),
          task_exec(_task_exec)
    {
        navigationController = objectFactory->createNavigationController(masterController);
        commandController = objectFactory->createCommandController(masterController, navigationController);
        viewController = objectFactory->createViewController(masterController);
        userController = objectFactory->createUserController(masterController, nullptr);
        taskExecutorCallbackBinder = objectFactory->createTaskExecutorCallbackBinder(masterController, task_exec);
        serviceController = objectFactory->createServiceController(masterController, commandController,
                                                                   taskExecutorCallbackBinder, userController,
                                                                   viewController);
    }

    IObjectFactory* objectFactory{nullptr};
    MasterController* masterController{nullptr};
    INavigationController* navigationController{nullptr};
    ICommandController* commandController{nullptr};
    ViewController* viewController{nullptr};
    TaskExecuterRunner* task_exec{nullptr};

    IUserController* userController{nullptr};
    services::TaskExecutorCallbackBinder* taskExecutorCallbackBinder{nullptr};
    ServiceController* serviceController{nullptr};

    QString welcomeMessage = "Welcome to the Chat!";

};

MasterController::MasterController(QObject *parent, IObjectFactory* objectFactory, TaskExecuterRunner* task)
    : QObject(parent)
{
    implementation.reset(new Implementation(this, objectFactory, task));
}

MasterController::~MasterController(){}

INavigationController* MasterController::navigationController()
{
    return implementation->navigationController;
}

ICommandController* MasterController::commandController()
{
    return implementation->commandController;
}

ViewController* MasterController::viewController()
{
    return implementation->viewController;
}

ServiceController* MasterController::serviceController()
{
    return implementation->serviceController;
}

const QString& MasterController::welcomeMessage() const
{
    return implementation->welcomeMessage;
}

}
}

