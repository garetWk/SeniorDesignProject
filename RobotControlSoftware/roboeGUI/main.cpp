#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlContext>
#include <QSslCipher>
#include <QSslSocket>
#include <QSslError>
#include <QSslCertificate>
#include <QSslKey>
#include <QQmlComponent>
#include <iostream>

#include <QTcpSocket>
#include "mysocket.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;

    MySocket socket;
    engine.rootContext()->setContextProperty("socket",&socket);

    /*
    if (QSslSocket::supportsSsl()) {

        cout << "start socket configure" << endl;
        QSslSocket socket;
        QSslCertificate ca_cert;

        socket.setProtocol(QSsl::AnyProtocol);
        socket.setPrivateKey(QStringLiteral("./client.key"));
        socket.setLocalCertificate(QStringLiteral("./client.crt"));

        ca_cert.fromPath(QStringLiteral("/Users/gwkaiser/Desktop/server.crt"));
        socket.addCaCertificate(ca_cert);

        socket.addCaCertificates(QStringLiteral("./server.crt"));

        socket.setPeerVerifyMode(QSslSocket::VerifyNone);


        cout << "protocol: " << socket.protocol() << endl;
        cout << "verify mode: " << socket.peerVerifyMode() << endl;
        cout << "connecting to host" << endl;
        socket.connectToHostEncrypted(QStringLiteral("127.0.0.1"),50007);

        engine.rootContext()->setContextProperty("socket",&socket);

        cout << "connected to host" << endl;

    }
    */

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
