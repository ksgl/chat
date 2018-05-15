#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <controllers/master-controller.h>
#include <controllers/navigation-controller.h>
#include <controllers/i-command-controller.h>
#include <data/string-decorator.h>
#include <framework/command.h>
#include <framework/object-factory.h>

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
     QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    qmlRegisterType<chat::controllers::MasterController>("CHAT", 1, 0, "MasterController");

    qmlRegisterUncreatableType<chat::controllers::INavigationController>("CHAT", 1, 0, "INavigationController", "Interface");
    qmlRegisterUncreatableType<chat::controllers::ICommandController>("CHAT", 1, 0, "ICommandController", "Interface");

    qmlRegisterType<chat::framework::Command>("CHAT", 1, 0, "Command");
    qmlRegisterType<chat::data::StringDecorator>("CHAT", 1, 0, "StringDecorator");

    chat::framework::ObjectFactory objectFactory;
    chat::controllers::MasterController masterController(nullptr, &objectFactory);

    QQmlApplicationEngine engine;
    engine.addImportPath("qrc:/");
    engine.rootContext()->setContextProperty("masterController", &masterController);
    engine.load(QUrl(QStringLiteral("qrc:/views/MainView.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
