#include "IContext.h"
#include <QFile>
#include <QStandardPaths>

#include <src/core/Logger.h>

IContext::IContext() 
{  
	_startTime = QDateTime::currentDateTime();
	
	_accMgr = new AccountManager();
	_procConsole = new ConsoleProc();
	_procConsole->start();
	
	_urlValidator.setPattern("^(http(s)?:\\/\\/(([a-zA-Z-_\\.0-9])+\\.([a-zA-Z]{2,})|([0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}))((\\:)?[0-9]{1,5})?(\\/([a-zA-Z0-9-_\\.])*)*(\\?[\\w\\-]+\\=[\\w\\-]*(\\&)?)*)$");
	
	LOG_DEBUG << "Check main folder";
	QDir dir(getDefaultPath());
	if (!dir.exists())
	{
		if (!dir.mkpath(getDefaultPath()))
		{
			throw std::runtime_error("Can't create application's main folder!");
		}
	}
	
	_lockFile.setFileName(dir.absoluteFilePath(".lock"));
	
	// TODO: Перенести эти костыли на реальное 
	// получение данных из конфига
	_nodeHostAddress = QHostAddress::Any;
	_nodePort = 63975;
	//node.add("http://127.0.0.1:63975/");
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

QString IContext::getDefaultPath()
{
	LOG_TRACE;
	
	
#ifdef __linux
	QString appDataPath = QDir::homePath();
	LOG_DEBUG << "Home path" << appDataPath;

	return appDataPath.append("/.stupid");
#else
	QString appDataPath = QStandardPaths::standardLocations(QStandardPaths::AppDataLocation).at(0);
	LOG_DEBUG << "APPDATA path" << appDataPath;

	return appDataPath.append("/stupid");
#endif
}

QString IContext::getDefaultDatabasePath()
{
	LOG_TRACE;
	
	return getDefaultPath().append("/db");
}

void IContext::lockMainFolder()
{
	LOG_TRACE;
	
	//TODO: не работает!
	if (!_lockFile.open(QIODevice::WriteOnly))
	{
		throw std::runtime_error("Locking of main directory failed!");
	}
	_lockFile.write(QDateTime::currentDateTime().toString().toUtf8());
}

void IContext::unlockMainFolder()
{
	LOG_TRACE;
	_lockFile.close();
}

QDateTime IContext::startTime()
{
	return _startTime;
}

