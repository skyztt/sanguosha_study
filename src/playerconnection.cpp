#include "playerconnection.h"
#include "QTcpSocket"

PlayerConnection::PlayerConnection(QTcpSocket *socket, QObject *parent)
	: QObject(parent),
	socket_(socket)
{
	connect(socket_, SIGNAL(disconnected()), this, SIGNAL(disconnected()));
	connect(socket_, &QTcpSocket::readyRead, this, [this]() {
		while (socket_->canReadLine()) {
			QString request = socket_->readLine(1024);
			request.chop(1);
			emit getMessageFromPlayer(request, getUuidString());
		}
	});
}

void PlayerConnection::sendMessageToPlayer(const QString& msg)
{
	Q_ASSERT(socket_);
	if (socket_) {
		socket_->write(msg.toUtf8());
		socket_->write("\n");
	}
}

PlayerConnection::~PlayerConnection()
{

}

QString PlayerConnection::getUuidString()
{
	return player_.getUuidString();
}
