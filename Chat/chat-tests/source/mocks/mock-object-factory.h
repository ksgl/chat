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

};

}}

#endif
