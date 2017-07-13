#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>

class Client : public QTcpSocket
{
Q_OBJECT
public:
    explicit Client(QObject *parent = 0);
	void request(const QString &message);
	void signup();

signals:
    void errorMessage(const QString &msg);

private slots:
    void raiseError(QAbstractSocket::SocketError socket_error);
	void dealWithMessage();
};

#endif // CLIENT_H
