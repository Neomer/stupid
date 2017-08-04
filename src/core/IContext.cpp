#include "IContext.h"
#include <QFile>
#include <src/core/Logger.h>

IContext::IContext() 
{  
	_accMgr = new AccountManager();
	_procConsole = new ConsoleProc();
	_procConsole->start();
	
	_urlValidator.setPattern("^(http(s)?:\\/\\/([a-zA-Z-_\\.0-9])+\\.([a-zA-Z]{2,})(\\/([a-zA-Z0-9-_\\.])*)*(\\?[\\w\\-]+\\=[\\w\\-]*(\\&)?)*)$");
	
	
	// TODO: Перенести эти костыли на реальное 
	// получение данных из конфига
	_nodeHostAddress = QHostAddress::Any;
	_nodePort = 25789;
	_nodeList << QUrl("http://127.0.0.1:80/stupid");
}

IContext::~IContext() 
{  
	delete _accMgr;
	delete _procConsole;
}


void IContext::loadSettings(QString filename)
{
	LOG_TRACE << filename;
	
	if (!QFile::exists(filename))
	{
		LOG_CRIT << "File not found!" << filename;
		throw std::runtime_error("Configuration fiole not found!");
	}
}

void IContext::saveSettings(QString filename)
{
	LOG_TRACE << filename;
	
	//TODO: сделать сохранение настроек
}

void IContext::addNode(QUrl node)
{
	LOG_TRACE << node.toString();
	
	_nodeList << node;
	
	LOG_INFO << "Node added! Total count:" << _nodeList.size();
}

