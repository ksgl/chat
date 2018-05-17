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
        newChatModel = new models::ChatModel(masterController);
        newMessage = new models::Message(masterController);
    }

    IObjectFactory* objectFactory{nullptr};
    MasterController* masterController{nullptr};
    INavigationController* navigationController{nullptr};
    ICommandController* commandController{nullptr};
    models::ChatModel* newChatModel{nullptr};
    models::Message* newMessage{nullptr};


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

models::ChatModel* MasterController::newChatModel()
{
    return implementation->newChatModel;
}

models::Message* MasterController::newMessage()
{
    return implementation->newMessage;
}

}
}

