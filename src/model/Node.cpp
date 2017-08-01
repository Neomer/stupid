#include "Node.h"
#include <src/core/Logger.h>
#include <src/core/IBus.h>


Node::Node(QObject *parent) : 
	QTcpServer(parent)
{
	LOG_TRACE;
	
	connect(this, SIGNAL(newConnection()), this, SLOT(applyConnection()));
}

void Node::applyConnection()
{
	LOG_TRACE;
	
	QTcpSocket *sock = this->nextPendingConnection();
	
	LOG_DEBUG << "New connection IP:" << sock->peerAddress().toString();
	
	_peers.append(new Peer(sock, this));
	
	busConsole::instance().publish("net.newPeer");
}

