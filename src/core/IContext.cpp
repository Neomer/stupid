#include "IContext.h"
#include <QFile>
#include <src/core/Logger.h>

IContext::IContext() 
{  
	_accMgr = new AccountManager();
	_procConsole = new ConsoleProc();
	_procConsole->start();
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

