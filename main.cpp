#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "gameengine.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<GameEngine>();

    QQmlApplicationEngine engine;
    GameEngine g;

    auto root_context = engine.rootContext();
    root_context ->setContextProperty("gameEngine", &g);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
