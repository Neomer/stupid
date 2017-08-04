#include "ConsoleProc.h"
#include <iostream>

ConsoleProc::ConsoleProc(QObject * parent) :
	QThread(parent),
	_stop(false)
{
	LOG_TRACE;
	
	_stream = new QTextStream(stdin);
	busConsole::instance().subscribe("system.exit", this);
}

ConsoleProc::~ConsoleProc()
{
	//terminate();
}

void ConsoleProc::run()
{
	LOG_TRACE;

	forever
	{
		std::cout << "> ";
		QString string = _stream->readLine();
		LOG_DEBUG << "Type command: " << string;
		busConsole::instance().publish("console.input", string.trimmed());
		if (_stop)
			return;
	}
}

bool ConsoleProc::onCommand(QString command, QVariant data)
{
	LOG_TRACE << command << data;
	
	if (command == "system.exit")
	{
		terminate();
	}
}

