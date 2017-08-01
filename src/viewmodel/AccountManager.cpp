#include "AccountManager.h"
#include <src/core/IBus.h>
#include <src/core/Logger.h>
#include <src/model/Account.h>

AccountManager::AccountManager(QObject *parent) : QObject(parent)
{
	busConsole::instance().subscribe("console.input", this);	
}

void AccountManager::create(QString password)
{
	LOG_TRACE << password;
	Account acc(this);
	acc.create(password);
}

bool AccountManager::onCommand(QString command, QVariant data)
{
	LOG_TRACE << command << data;
	
	
	if (command == "console.input")
	{
		QString method = EventBroker::parseMethod(data.toString());
		QStringList args = EventBroker::parseArguments(data.toString());
		LOG_DEBUG << "Method:" << method << "Num of arguments:" << args.count();

		if (method == "account.create")
		{
			if (args.count() != 1)
			{
				throw std::runtime_error("Wrong count of arguments!");
			}
			this->create(args.at(0));
			return false;
		}
	}
	return true;
}

