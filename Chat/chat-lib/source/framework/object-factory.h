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
};

}
}

#endif // OBJECTFACTORY_H
