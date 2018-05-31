#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <task-exec/TaskExecutor.hpp>
#include <task-exec/UDPServer.hpp>

#include <controllers/master-controller.h>
#include <controllers/navigation-controller.h>
#include <controllers/i-command-controller.h>
#include <framework/object-factory.h>

#include <views/login-view-model.h>
#include <views/registration-view-model.h>
#include <views/chat-list-model-view.h>

int main(int argc, char *argv[])
{
    TaskExecuterRunner task_runner;
    task_runner.start();

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    
    qmlRegisterType<chat::controllers::MasterController>("CHAT", 1, 0, "MasterController");
    
    qmlRegisterUncreatableType<chat::controllers::INavigationController>("CHAT", 1, 0, "INavigationController", "Interface");
    qmlRegisterUncreatableType<chat::controllers::ICommandController>("CHAT", 1, 0, "ICommandController", "Interface");

    qmlRegisterType<chat::controllers::ServiceController>("CHAT", 1, 0, "ServiceController");
    qmlRegisterType<chat::framework::Command>("CHAT", 1, 0, "Command");
    qmlRegisterType<chat::views::LoginViewModel>("CHAT", 1, 0, "LoginViewModel");
    qmlRegisterType<chat::views::RegistrationViewModel>("CHAT", 1, 0, "RegistrationViewModel");
    qmlRegisterType<chat::views::ChatListModelView>("CHAT", 1, 0, "ChatListModelView");
    qmlRegisterType<chat::views::FriendListViewModel>("CHAT", 1, 0, "FriendListViewModel");
    qmlRegisterType<chat::models::ChatModel>("CHAT", 1, 0, "ChatModel");
    qmlRegisterType<chat::data::StringDecorator>("CHAT", 1, 0, "StringDecorator");
    qmlRegisterType<chat::views::ChatDetailViewModel>("CHAT", 1, 0, "ChatDetailViewModel");
    qmlRegisterType<chat::models::Message>("CHAT", 1, 0, "Message");
    qmlRegisterType<chat::data::EnumeratorDecorator>("CHAT", 1, 0, "EnumeratorDecorator");
    qmlRegisterType<chat::data::DateTimeDecorator>("CHAT", 1, 0, "DateTimeDecorator");
    qmlRegisterType<chat::models::Friend>("CHAT", 1, 0, "Friend");

    chat::framework::ObjectFactory objectFactory;
    chat::controllers::MasterController masterController(nullptr, &objectFactory, &task_runner);

    //добавить таск менеджер, очередь
    
    QQmlApplicationEngine engine;
    engine.addImportPath("qrc:/");

    QQmlContext* context = engine.rootContext();
    context->setContextProperty("masterController", &masterController);

    engine.load(QUrl(QStringLiteral("qrc:/views/MainView.qml")));
    
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
