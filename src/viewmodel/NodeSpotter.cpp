#include "NodeSpotter.h"
#include <src/core/Logger.h>
#include <src/core/IBus.h>
#include <src/core/IContext.h>
#include <QNetworkRequest>

NodeSpotter::NodeSpotter(QObject *parent) : 
	QObject(parent),
	_netAccess(new QNetworkAccessManager(parent))
{
	LOG_TRACE;
	
	busConsole::instance().subscribe("console.input", this);
}

void NodeSpotter::updatePeers()
{
	LOG_TRACE;

	QList<QUrl>list = Context::instance().nodeList();
	foreach(QUrl url, list)
	{
		url.setQuery("method=peers.share");
		QNetworkRequest netRequest(url);
		_netAccess->get(netRequest);
	}
}

bool NodeSpotter::onCommand(QString command, QVariant data)
{
	LOG_TRACE << command << data;
	
	if (command == "console.input")
	{
		QString method = EventBroker::parseMethod(data.toString());
		QStringList args = EventBroker::parseArguments(data.toString());
		LOG_DEBUG << "Method:" << method << "Num of arguments:" << args.count();

		if (method == "node.add")
		{
			if (args.count() != 1)
			{
				throw std::runtime_error("Wrong count of arguments!");
			}
			LOG_DEBUG << "Adding new node...";
			
			QString sUrl = ((QString)args.at(0)).replace("\"", "").trimmed();
			
			if (Context::instance().getUrlValidator().indexIn(sUrl) == -1)
			{
				throw std::runtime_error("Wrong format of node's URL!");
			}
			
			QUrl url(sUrl, QUrl::StrictMode);
			if (!url.isValid())
			{
				throw std::runtime_error("Wrong format of node's URL!");
			}
			
			LOG_DEBUG << "Node's URL is" << url.toString();
			Context::instance().addNode(url);
			
			return false;
		}
		else if (method == "peers.update") 
		{
			if (args.count() != 0)
			{
				throw std::runtime_error("Wrong count of arguments!");
			}

			LOG_DEBUG << "Updating information about peers...";
			updatePeers();
			
			return false;
		}
		else if (method == "node.list")
		{
			if (args.count() != 0)
			{
				throw std::runtime_error("Wrong count of arguments!");
			}
			
			QList<QUrl>list = Context::instance().nodeList();
			foreach(QUrl url, list)
			{
				LOG_INFO << url.toString();
			}
			return false;
		}
	}
	return true;
}

