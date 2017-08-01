#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QObject>
#include <src/core/EventBroker.h>

class Account : public QObject, public EventBroker
{
	Q_OBJECT
public:
	explicit Account(QObject *parent = 0);
	
	bool load(QString password);
	void create(QString password);
	
	// EventBroker interface
protected:
	bool onCommand(QString command, QVariant data);
};

#endif // ACCOUNT_H
