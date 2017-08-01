#ifndef CONSOLEPROC_H
#define CONSOLEPROC_H

#include <QObject>
#include <QThread>
#include <QTextStream>

#include <src/core/Logger.h>
#include <src/core/IBus.h>

class ConsoleProc : public QThread, public EventBroker
{
	Q_OBJECT
	
public:
	ConsoleProc(QObject * parent = 0);
	~ConsoleProc();
			
protected:
	void run();
	
private:
	QTextStream *_stream;
	bool _stop;
	
	// EventBroker interface
protected:
	bool onCommand(QString command, QVariant data);
};

#endif // CONSOLEPROC_H
