#include "Node.h"
#include <src/core/Logger.h>
#include <src/core/IBus.h>
#include <src/core/IContext.h>

Node::Node() : 
	QTcpServer()
{
	LOG_TRACE;
	
	LOG_DEBUG << "Try to set listenning socket" 
			  << Context::instance().getNodeHostAddress().toString()
			  << ":" 
			  << Context::instance().getNodePort();

	if (!this->listen(Context::instance().getNodeHostAddress(),
				 Context::instance().getNodePort()))
	{
		LOG_CRIT << "Can't bind node!" 
				 << Context::instance().getNodeHostAddress().toString()
				 << ":" 
				 << Context::instance().getNodePort();
		
		throw std::runtime_error("Can't bind node!");
	}
	
	LOG_DEBUG << "Socket is ready for connections!";
	connect(this, SIGNAL(newConnection()), this, SLOT(applyConnection()));
	
	busConsole::instance().subscribe("net.income", this);
	busConsole::instance().subscribe("net.newPeer", this);
}

Node::~Node()
{
	LOG_TRACE;
}

bool Node::onCommand(QString command, QVariant data)
{
	LOG_TRACE << command << data;
	
	if (command == "net.income")
	{
		QString method = EventBroker::parseMethod(data.toString());
		QStringList args = EventBroker::parseArguments(data.toString());

		LOG_DEBUG << "Method:" << method << "Num of arguments:" << args.count();
		if (method == "peers.share")
		{
			busConsole::instance().publish("net.send", "peers.share(\"{\"peers\": [\"127.0.0.1:25678\"]}\");");
			return false;
		}
	}
	else if (command == "net.newPeer")
	{
		LOG_TRACE << "Total peers:" << _peers.count();
	}
	return true;
}

void Node::applyConnection()
{
	LOG_TRACE;
	
	QTcpSocket *sock = this->nextPendingConnection();
	
	LOG_DEBUG << "New connection IP:" << sock->peerAddress().toString();
	
	_peers.append(new Peer(sock, this));
	
	busConsole::instance().publish("net.newPeer");
}

