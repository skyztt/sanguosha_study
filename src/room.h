#ifndef ROOM_H
#define ROOM_H

#include <QObject>
#include "player.h"
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
	QList<QSharedPointer<Player>> pList_;	
};

#endif // ROOM_H
