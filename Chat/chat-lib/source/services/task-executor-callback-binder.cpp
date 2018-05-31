#include "task-executor-callback-binder.h"

#include <QJsonObject>

using namespace chat::framework;
using namespace std;

namespace chat {
namespace services {

//typedef pair<string*, CallbackPtr<ITaskExecutorCallbackBinder, int>> NameCallbackPair;

class TaskExecutorCallbackBinder::Implementation
{
public:
    Implementation(TaskExecutorCallbackBinder* _taskExecutorCallbackBinder, TaskExecuterRunner* _task_exec)
        : taskCallbackBinder(_taskExecutorCallbackBinder), task_exec(_task_exec)
    {
        task_exec->set_orphan_message_callback([this](nlohmann::json json){ switchCommands(json) });
    }

    TaskExecutorCallbackBinder* taskCallbackBinder{nullptr};
    TaskExecuterRunner* task_exec{nullptr};
};

TaskExecutorCallbackBinder::TaskExecutorCallbackBinder(QObject *parent, TaskExecuterRunner *task_exec) : QObject(parent)
{
    implementation.reset(new Implementation(this, task_exec));
}

TaskExecutorCallbackBinder::~TaskExecutorCallbackBinder(){}

int TaskExecutorCallbackBinder::switchCommands(nlohmann::json json)
{
    std::string str_json = json.dump();
    QString q_str(str_json.c_str());
    QJsonDocument doc = QJsonDocument::fromJson(q_str.toUtf8());
    models::NetCommandModel net_command(this, doc.object());

    QString commandType = net_command.command_type->value();

    if (commandType == "user.login")
        emit LoginAnswerReceived(&net_command.payload);

    else if (commandType == "user.register")
        emit RegisterAnswerReceived(net_command.payload);

    else if (commandType == "user.message_send")
        emit MessageReceived(net_command.payload);

    else if (commandType == "user.add_friend")
        emit FriendReceived(net_command.payload);
}

void TaskExecutorCallbackBinder::sendNetTask(QJsonObject &netTask)
{
    QJsonDocument doc(netTask);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    std::string std_json = strJson.toStdString();
    nlohmann::json n_lh_str = nlohmann::json::parse(std_json);

    implementation->task_exec->execute_async(n_lh_str, [](nlohmann::json json){});
}


}
}

