#ifndef PLAYERCONNECTION_H
#define PLAYERCONNECTION_H

#include <QObject>
#include <QUuid>
#include "player.h"

class QTcpSocket;
class PlayerConnection : public QObject
{
	Q_OBJECT

public:
	PlayerConnection(QTcpSocket *socket ,QObject *parent = nullptr);

	void sendMessageToPlayer(const QString& msg);
	~PlayerConnection();

	QTcpSocket *getInnerSocket() {
		Q_ASSERT(socket_);
		return socket_;
	}	
	QString getUuidString();
signals:
	void disconnected();
	void getMessageFromPlayer(const QString& msg, const QString& strUUid);
private:
	QTcpSocket *socket_ = nullptr;	
	Player player_;
};

#endif // PLAYERCONNECTION_H
