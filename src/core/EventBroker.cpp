#include "EventBroker.h"
#include <src/core/Logger.h>

EventBroker::EventBroker()
{
	
}

QStringList EventBroker::parseArguments(QString data)
{
	data = data.trimmed();
	LOG_TRACE << data;  
	
// .*\..*\((.)*\)\s*;
	
	QStringList ret;

	int bracket = data.indexOf('('), 
			tmp;
	if (bracket == -1)
	{
		return ret;
	}
	
	
	while ((tmp = data.indexOf(',', bracket)) != -1)
	{
		ret << data.mid(bracket + 1, tmp - bracket - 1);
		bracket = tmp + 1;
	}
	tmp = data.lastIndexOf(')');
	
	if (tmp == -1)
	{
		throw std::runtime_error("Wrong format!");
	}
	
	QString param = data.mid(bracket + 1, tmp - bracket - 1).trimmed();
	if (!param.isEmpty())
	{
		ret << param;
	}
	
	return ret;
	
}

QString EventBroker::parseMethod(QString data)
{
	data = data.trimmed();
	LOG_TRACE << data;
	
	int bracket = data.indexOf('(');
	if (bracket == -1)
	{
		throw std::runtime_error("Wrong format!");
	}
	
	return data.mid(0, bracket).toLower();
}

