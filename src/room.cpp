#include "room.h"

Room::Room(QObject *parent)
	: QObject(parent)
{

}

void Room::addConnection(QTcpSocket *socket)
{
	QSharedPointer<Player> p(new Player(socket));
	pList_.append(p);
	connect(p.data(), &Player::getMessageFromPlayer, this, &Room::log);
}

Room::~Room()
{

}
