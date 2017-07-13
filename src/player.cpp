#include "player.h"
#include "QTcpSocket"

Player::Player(QTcpSocket *socket, QObject *parent)
	: QObject(parent),
	socket_(socket),
	id_(QUuid::createUuid())
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

void Player::sendMessageToPlayer(const QString& msg)
{
	Q_ASSERT(socket_);
	if (socket_) {
		socket_->write(msg.toUtf8());
		socket_->write("\n");
	}
}

Player::~Player()
{

}

QString Player::getUuidString()
{
	return id_.toString();
}
