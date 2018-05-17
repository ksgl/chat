#include "object-factory.h"

#include <controllers/navigation-controller.h>
#include <controllers/command-controller.h>

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

}
}
