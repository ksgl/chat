#ifndef TASKEXECUTORCALLBACKBINDER_H
#define TASKEXECUTORCALLBACKBINDER_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>

#include <chat-lib_global.h>
#include <framework/callback.h>

#include <task-exec/json.hpp>
#include <task-exec/TaskExecutor.hpp>
#include <models/net-command-model.h>
#include <services/i-task-executor-callback-binder.h>

namespace chat {
namespace services {

class CHATLIBSHARED_EXPORT TaskExecutorCallbackBinder : public QObject
{
    Q_OBJECT
public:
    explicit TaskExecutorCallbackBinder(QObject *parent = nullptr, TaskExecuterRunner* task_exec = nullptr);
    ~TaskExecutorCallbackBinder();

signals:

    void LoginAnswerReceived(models::PayloadModel&);
    void RegisterAnswerReceived(models::PayloadModel&);
    void MessageReceived(models::PayloadModel&);
    void FriendReceived(models::PayloadModel&);

public slots:
    void sendNetTask(QJsonObject& netTask);
    int switchCommands(nlohmann::json json);

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;

};

}
}


#endif // TASKEXECUTORCALLBACKBINDER_H
