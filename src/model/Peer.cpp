#include "Peer.h"
#include <src/core/Logger.h>
#include <src/core/IBus.h>

Peer::Peer(QTcpSocket *socket, QObject *parent) : 
	QObject(parent),
	_socket(socket)
{
	LOG_TRACE;
}

void Peer::readBytes()
{
	LOG_TRACE;
	
	QByteArray buffer = _socket->readAll();
	
	LOG_DEBUG << "Received" << buffer.size() << "byte(s)";
	
	busConsole::instance().publish("net.income", buffer);
}

