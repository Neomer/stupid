#ifndef APP_H
#define APP_H

#include <QCoreApplication>
#include <QObject>
#include <src/core/IBus.h>

class App : public QCoreApplication, public EventBroker
{
	Q_OBJECT
public:
	explicit App(int argc, char *argv[]);
	
	
	// EventBroker interface
protected:
	bool onCommand(QString command, QVariant data);
};

#endif // APP_H
