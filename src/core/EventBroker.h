#ifndef EVENTBROKER_H
#define EVENTBROKER_H

#include <QString>
#include <QVariant>

class EventBroker
{
	friend class IBus;
	
public:
	EventBroker();
	
	static QStringList parseArguments(QString data);
	static QString parseMethod(QString data);
	
protected:
	virtual bool onCommand(QString command, QVariant data = QVariant()) = 0;
};

#endif // EVENTBROKER_H
