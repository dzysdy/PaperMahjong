#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <CppInterface.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<CppInterface>("cppinterface", 1, 0, "CppInterface");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("../TileLogic/main.qml")));

    return app.exec();
}
