#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <data.h>
#include <udpreceiver.h>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<Data>("backend.Data", 1, 0, "Data");

    QQmlApplicationEngine engine;
    Data backendData;
    SimpleServer receiver;
    receiver.setAzimutSetFunc([&](float azimut) {backendData.setAzimut(azimut);});
    receiver.setErrorQntSetFunt([&](int qnt) {backendData.setErrorQnt(qnt);});
    receiver.setPortGetFunc([&]()->int{return backendData.port();});
    engine.rootContext()->connect(&backendData, &Data::startUdpSignal, &receiver, &SimpleServer::socketConnect);
    engine.rootContext()->connect(&receiver, &SimpleServer::udpConnectedSignal, &backendData, &Data::udpConnected);
    engine.rootContext()->connect(&receiver, &SimpleServer::udpDisconnectedSignal, &backendData, &Data::udpDisconnected);
    engine.rootContext()->setContextProperty("backendData", &backendData);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
