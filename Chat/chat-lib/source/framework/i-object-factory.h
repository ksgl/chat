#ifndef IOBJECTFACTORY_H
#define IOBJECTFACTORY_H

#include <controllers/i-navigation-controller.h>
#include <controllers/i-command-controller.h>

namespace chat {
namespace framework {

class IObjectFactory
{
public:
    virtual ~IObjectFactory(){}

    virtual controllers::INavigationController* createNavigationController(QObject* parent) const = 0;
    virtual controllers::ICommandController* createCommandController(QObject* parent, controllers::INavigationController* navigationController) const = 0;
};

}

}
#endif // IOBJECTFACTORY_H
