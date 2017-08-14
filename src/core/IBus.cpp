#include "IBus.h"
#include <QMetaObject>

#include <src/core/Logger.h>
#include <src/core/IContext.h>

void IBus::subscribe(QString event, EventBroker *broker)
{
	LOG_TRACE << event << broker;
	
	_mtx.lock();
	
	if (_map.contains(event))
	{
		_map[event].append(broker);
	}
	else
	{
		QList<EventBroker *> list;
		list.append(broker);
		_map.insert(event, list);
	}
	
	_mtx.unlock();
}

void IBus::unsubscribe(QString event, EventBroker *broker)
{
	LOG_TRACE << event << broker;
	
	_mtx.lock();
	if (_map.contains(event))
	{
		if (_map[event].contains(broker))
		{
			_map[event].removeOne(broker);
			if (_map[event].count() == 0)
			{
				LOG_DEBUG << "Event catcher list is empty. Remove event from tube!";
				_map.remove(event);
			}
		}
	}
	_mtx.unlock();
}

void IBus::publish(QString event, QVariant data)
{
	LOG_TRACE << event << data;
	
	QList<EventBroker *> list;
	_mtx.lock();
	if (_map.contains(event))
	{
		list = _map[event];
	}
	_mtx.unlock();
	
	
	LOG_DEBUG << "Total event catchers: " << list.count();
	for (int i = 0; i < list.count(); i++)
	{
		try {
			if (!list.at(i)->onCommand(event, data))
			{
				LOG_INFO << "Command complete!";
				return;
			}
		}
		catch (std::exception &ex) {
			LOG_CRIT << ex.what();
			return;
		}
	}
	if (Context::instance().consoleProcessor()->isRunning())
	{
		LOG_INFO << "Unknown command!";
	}
}
