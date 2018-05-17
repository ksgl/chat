#ifndef MASTERCONTROLLER_H
#define MASTERCONTROLLER_H

#include <QObject>
#include <QString>
#include <QScopedPointer>

#include <chat-lib_global.h>
#include <framework/i-object-factory.h>
#include <controllers/i-navigation-controller.h>
#include <controllers/i-command-controller.h>
#include <models/chat-model.h>

namespace chat {
namespace controllers {

class MasterController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(chat::controllers::INavigationController* ui_navigationController READ navigationController CONSTANT)    
    Q_PROPERTY(chat::controllers::ICommandController* ui_commandController READ commandController CONSTANT)
    Q_PROPERTY( QString ui_welcomeMessage READ welcomeMessage CONSTANT )

    Q_PROPERTY(chat::models::ChatModel* ui_newChatModel READ newChatModel CONSTANT)
    //Q_PROPERTY(chat::models::Message* ui_newMessage MEMBER newMessage CONSTANT)
    Q_PROPERTY(chat::models::Message* ui_newMessage READ newMessage CONSTANT)

public:
    explicit MasterController(QObject *parent = nullptr, framework::IObjectFactory* objectFactory = nullptr);
    ~MasterController();

    INavigationController* navigationController();
    ICommandController* commandController();

    const QString& welcomeMessage() const;
    models::ChatModel* newChatModel();
    models::Message* newMessage();

signals:

public slots:

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;
};

}
}

#endif // MASTERCONTROLLER_H
