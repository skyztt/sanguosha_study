#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QUuid>

class QTcpSocket;
class Player : public QObject
{
	Q_OBJECT

public:
	Player(QTcpSocket *socket ,QObject *parent = nullptr);

	void sendMessageToPlayer(const QString& msg);
	~Player();

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
	QUuid id_;
};

#endif // PLAYER_H
