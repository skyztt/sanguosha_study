#include "client.h"
#include "settings.h"

Client::Client(QObject *parent) :
    QTcpSocket(parent)
{
    connectToHost(Config.HostAddress, Config.Port);

    connect(this, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(raiseError(QAbstractSocket::SocketError)));
	connect(this, &QIODevice::readyRead, this, &Client::dealWithMessage);
	connect(this, &QAbstractSocket::connected, this, [this]() {
		signup();
	});
}

void Client::request(const QString &message)
{
	write(message.toUtf8());
	write("\n");
}

void Client::signup()
{
	setProperty("name", Config.UserName);
	setProperty("avatar", Config.userGeneral);

	request(QString("signup %1 %2").arg(Config.UserName).arg(Config.userGeneral));
}

void Client::raiseError(QAbstractSocket::SocketError socket_error){
    // translate error message
    QString reason;
    switch(socket_error){
    case ConnectionRefusedError: reason = tr("Connection was refused or timeout"); break;
    case RemoteHostClosedError: reason = tr("Remote host close this connection"); break;
        // FIXME
    default: reason = tr("Unknow error"); break;
    }

    emit errorMessage(tr("Connection failed, error code = %1\n reason:\n %2").arg(socket_error).arg(reason));
}

void Client::dealWithMessage()
{
	
}
