#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
class Room;

class Server : public QTcpServer
{
Q_OBJECT
public:
    explicit Server(QObject *parent = 0);
	bool start();
private:
	Room *room_ = nullptr;
signals:
	void server_message(const QString&);
private slots:
    void processNewConnection();
};

#endif // SERVER_H
