#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H

#include <QObject>
#include <src/core/EventBroker.h>

class AccountManager : public QObject, public EventBroker
{
	Q_OBJECT
	
public:
	explicit AccountManager(QObject *parent = 0);
	
public slots:
	void create(QString password);
	
protected:
	bool onCommand(QString command, QVariant data);
};

#endif // ACCOUNTMANAGER_H
