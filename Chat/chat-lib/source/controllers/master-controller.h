#ifndef MASTERCONTROLLER_H
#define MASTERCONTROLLER_H

#include <QObject>
#include <QString>
#include <QScopedPointer>

#include <task-exec/TaskExecutor.hpp>

#include <chat-lib_global.h>
#include <framework/i-object-factory.h>
#include <controllers/i-navigation-controller.h>
#include <controllers/i-command-controller.h>
#include <controllers/view-controller.h>
#include <controllers/i-user-controller.h>
#include <controllers/service-controller.h>
#include <services/task-executor-callback-binder.h>
#include <models/user-model.h>

namespace chat {
namespace controllers {

class MasterController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(chat::controllers::INavigationController* ui_navigationController READ navigationController CONSTANT)
    Q_PROPERTY(chat::controllers::ICommandController* ui_commandController READ commandController CONSTANT)
    Q_PROPERTY(chat::controllers::ViewController* ui_viewController READ viewController CONSTANT)
    Q_PROPERTY( QString ui_welcomeMessage READ welcomeMessage CONSTANT )
    Q_PROPERTY(chat::controllers::ServiceController* ui_serviceController READ serviceController CONSTANT)
public:
    explicit MasterController(QObject *parent = nullptr, framework::IObjectFactory* objectFactory = nullptr, TaskExecuterRunner* task_exec = nullptr);
    ~MasterController();

    INavigationController* navigationController();
    ICommandController* commandController();
    ViewController* viewController();
    ServiceController* serviceController();

    const QString& welcomeMessage() const;

signals:

public slots:

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;
};

}
}

#endif // MASTERCONTROLLER_H
