#include "server.h"
#include "settings.h"
#include "room.h"
#include "QTcpServer"
#include "QTcpSocket"

Server::Server(QObject *parent) :
    QTcpServer(parent)
{
}

bool Server::start(){
    quint16 port = Config.Port;

    connect(this, SIGNAL(newConnection()), this, SLOT(processNewConnection()));

	emit server_message(tr("Server start: (%1: %2)").arg("127.0.0.1").arg(port));
    return listen(QHostAddress::LocalHost, port);
}

void Server::processNewConnection(){
    QTcpSocket *socket = nextPendingConnection();
	if (!room_) {
		room_ = new Room(this);
		connect(room_, &Room::log, this, &Server::server_message);
	}
	room_->addConnection(socket);

	emit server_message(tr("Client connected: (%1: %2)").arg(socket->peerAddress().toString()).arg(socket->peerPort()));
}
