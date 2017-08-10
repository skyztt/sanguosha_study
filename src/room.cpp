#include "room.h"
#include "QSet"
#include <QVariant> 


Room::Room(QObject *parent)
	: QObject(parent)
{

}

void Room::addConnection(QTcpSocket *socket)
{
	QSharedPointer<PlayerConnection> p(new PlayerConnection(socket));
	pList_.append(p);
	connect(p.data(), &PlayerConnection::getMessageFromPlayer, this, [this](const QString& msg, const QString& strUUid) {
		for (auto player : pList_) {
			if (player->getUuidString() == strUUid) {
				QStringList args = msg.split(" ");
				QString command = args.front();

				if (command == "set") {
					QString field = args[1];
					QString value = args[2];
					player->setProperty(field.toUtf8(), value);
				}
				else if (command == "signup") {
					QString name = args[1];
					QString avatar = args[2];

					player->setObjectName(name);
					player->setProperty("avatar", avatar);

					// introduce the new joined player to existing players except himself
					broadcast(QString("! addPlayer %1:%2").arg(name).arg(avatar), { player });
				}
				break;
			}
		}
		emit log(QString(msg) + "from : " + strUUid);
	});
}

Room::~Room()
{

}

void Room::unicast(const QString& msg, QSharedPointer<PlayerConnection> player)
{
	player->sendMessageToPlayer(msg);
}

void Room::broadcast(const QString& msg, QSet<QSharedPointer<PlayerConnection>> exceptPlayers)
{
	for (auto player : pList_) {
		if (!exceptPlayers.contains(player)) {
			player->sendMessageToPlayer(msg);
		}
	}
}
