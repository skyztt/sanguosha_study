#ifndef ROOM_H
#define ROOM_H

#include <QObject>
#include "playerconnection.h"
#include <QSharedPointer>

class QTcpSocket;

class Room : public QObject
{
	Q_OBJECT

public:
	Room(QObject *parent);
	void addConnection(QTcpSocket *socket);

	~Room();
signals :
	void log(const QString& msg);
private:
	void unicast(const QString& msg, QSharedPointer<PlayerConnection> player);
	void broadcast(const QString& msg, QSet<QSharedPointer<PlayerConnection>> exceptPlayers);
	QList<QSharedPointer<PlayerConnection>> pList_;	
};

#endif // ROOM_H
