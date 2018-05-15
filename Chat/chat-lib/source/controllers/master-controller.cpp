#include "master-controller.h"

using namespace chat::framework;

namespace chat {
namespace controllers {

class MasterController::Implementation {

public:
    Implementation(MasterController* _masterController, IObjectFactory* _objectFactory)
        : masterController(_masterController),
          objectFactory(_objectFactory)
    {
        navigationController = objectFactory->createNavigationController(masterController);
        commandController = objectFactory->createCommandController(masterController, navigationController);
    }

    IObjectFactory* objectFactory{nullptr};
    MasterController* masterController{nullptr};
    INavigationController* navigationController{nullptr};
    ICommandController* commandController{nullptr};

    QString welcomeMessage = "Welcome to the Chat!";

};

MasterController::MasterController(QObject *parent, IObjectFactory* objectFactory)
    : QObject(parent)
{
    implementation.reset(new Implementation(this, objectFactory));
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

const QString& MasterController::welcomeMessage() const
{
    return implementation->welcomeMessage;
}

}
}

