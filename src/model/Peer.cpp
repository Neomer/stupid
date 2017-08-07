#include "Peer.h"
#include <src/core/Logger.h>
#include <src/core/IBus.h>
#include <QNetworkRequest>

Peer::Peer(QTcpSocket *socket, QObject *parent) : 
	QObject(parent),
	_socket(socket)
{
	LOG_TRACE;
	
	connect(socket, SIGNAL(readyRead()), this, SLOT(readBytes()));
	IBus::instance().subscribe("net.send", this);
}

void Peer::readBytes()
{
	LOG_TRACE;
	
	QByteArray buffer = _socket->readAll();
	
	LOG_DEBUG << "Received" << buffer.size() << "byte(s)";
	
	busConsole::instance().publish("net.income", buffer);
}

bool Peer::onCommand(QString command, QVariant data)
{
	LOG_TRACE << command << data;
	
	if (command == "net.send")
	{
		QByteArray data_array = data.toByteArray();
		if (_socket->write(data_array) != data_array.size())
		{
			LOG_WARN << "Not all data were transmitted!";
		}
	}
	return true;
}

