#include "App.h"
#include <src/core/Logger.h>

App::App(int argc, char *argv[]) :
	QCoreApplication(argc, argv)
{
	LOG_TRACE;
	busConsole::instance().subscribe("console.input", this);
}

bool App::onCommand(QString command, QVariant data)
{
	LOG_TRACE;
	if (command == "console.input" && data.toString() == "exit")
	{
		busConsole::instance().publish("system.exit");
		this->quit();
		return false;
	}
	return true;
}

