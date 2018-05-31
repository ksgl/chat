#ifndef TASKFORMERSERVICE_H
#define TASKFORMERSERVICE_H

#include <QObject>

#include <chat-lib_global.h>
#include <models/message.h>
#include <models/net-command-model.h>

namespace chat {
namespace services {

class CHATLIBSHARED_EXPORT TaskFormerService : public QObject
{
    Q_OBJECT
public:
    explicit TaskFormerService(QObject *parent = nullptr);
    ~TaskFormerService();

public slots:

    QJsonObject& formLoginTask(QString& login, QString& password);
    QJsonObject& formRegisterTask(QString& login, QString& password);
    QJsonObject& formFriendRequestTask(QString& friendName);
    QJsonObject& formMessageSendTask(models::Message& message);

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;

};

}
}


#endif // TASKFORMERSERVICE_H
