#include "server.h"
#include <QDebug>

Server::Server(QObject *parent) : QTcpServer(parent) {}

void Server::startServer(quint16 port)
{
    if (!listen(QHostAddress::Any, port)) {
        qCritical() << "Failed to start server on port" << port << ":" << errorString();
        return;
    }
    qInfo() << "Server started on port" << port;
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    QTcpSocket *socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);

    connect(socket, &QTcpSocket::readyRead, this, &Server::onReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &Server::onDisconnected);

    qInfo() << "New connection from" << socket->peerAddress().toString();
}

void Server::onReadyRead()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if (!socket) return;

    QByteArray data = socket->readAll();
    qInfo() << "Received:" << data;

    // Echo back to client
    socket->write("Echo: " + data);
}

void Server::onDisconnected()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if (!socket) return;

    qInfo() << "Client disconnected:" << socket->peerAddress().toString();
    socket->deleteLater();
}
