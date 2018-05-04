#ifndef NAVIGATIONCONTROLLER_H
#define NAVIGATIONCONTROLLER_H

#include <QObject>

#include <chat-lib_global.h>
#include <controllers/i-navigation-controller.h>

namespace chat {
namespace controllers {

class CHATLIBSHARED_EXPORT NavigationController : public INavigationController
{
    Q_OBJECT
public:
    explicit NavigationController(QObject *parent = nullptr) : INavigationController(parent){}

signals:

public slots:
};

}
}

#endif // NAVIGATIONCONTROLLER_H
